#include <cmath>                  // roundf
#include <iostream>
//#define SEQAN_ENABLE_DEBUG 1
#if SEQAN_ENABLE_DEBUG
#include <ctime>                  // clock_t, clock, CLOCKS_PER_SEC
#endif

#include <seqan/arg_parse.h>
#include "mk_typedef.hpp"         // TRNATYPE, TCharSet, TRNASet, TIndexQGram, TFinder
#include "mk_input.hpp"           // MKInput
#include "pita_option.hpp"        // PITAOptions
#include "pita_seed_site.hpp"     // PITASeedSites
#include "pita_score.hpp"         // PITAMFEScores, PITATotalScores
#include "pita_site_cluster.hpp"  // PITAOverlap, PITATopNScore, PITASortedSitePos
#include "pita_core.hpp"          // PITACore

namespace ptddg {

int PITACoreMain(int argc, char const **argv) {
    int retVal;

    // Parse the command line.
    ptddg::PITAOptions options;
    seqan::ArgumentParser::ParseResult parseRes = options.parseCommandLine(argc, argv);
    if (parseRes != seqan::ArgumentParser::PARSE_OK) {
        return parseRes == seqan::ArgumentParser::PARSE_ERROR;
    }

    // Read input files
    mikan::MKInput coreInput;
    coreInput.set_options(options);
    retVal = coreInput.load_seq_from_file();
    if (retVal != 0) {
        return 1;
    }

    // Create index
    mikan::TRNASet const &mMRNASeqs = coreInput.get_mrna_seqs();
    mikan::TIndexQGram index(mMRNASeqs);
    mikan::TFinder finder(index);

    // Calculate scores for all miRNAs
    mikan::TCharSet const &mMiRNAIds = coreInput.get_mirna_ids();
    mikan::TRNASet const &mMiRNASeqs = coreInput.get_mirna_seqs();
    mikan::TCharSet const &mMRNAIds = coreInput.get_mrna_ids();

    ptddg::PITACore pitaCore(mMiRNAIds, mMiRNASeqs, mMRNAIds, mMRNASeqs, index, finder);
    pitaCore.init_from_args(options);
    pitaCore.open_output_file();
    retVal = pitaCore.calculate_all_scores();
    if (retVal != 0) {
        return 1;
    }

    return 0;
}

//
// PITACore methods
//
void PITACore::init_from_args(PITAOptions &opts) {
    mOutputAlign = opts.mOutputAlign;
    mOFileDDG = opts.mOFileSite;
    mOFileTotal = opts.mOFileTotal;
    mMinSeedLen = opts.mMinSeedLen;
    mMaxSeedLen = opts.mMaxSeedLen;

    resize(mSeedTypeDef, 5);
    mSeedTypeDef[0] = 'Y';
    mSeedTypeDef[1] = 'Y';
    mSeedTypeDef[2] = 'Y';
    if (opts.mMinSeedLen == 7) {
        mSeedTypeDef[0] = 'N';
    } else if (opts.mMinSeedLen == 8) {
        mSeedTypeDef[0] = 'N';
        mSeedTypeDef[1] = 'N';
    }

    if (opts.mMaxSeedLen == 7) {
        mSeedTypeDef[2] = 'N';
    } else if (opts.mMaxSeedLen == 6) {
        mSeedTypeDef[2] = 'N';
        mSeedTypeDef[1] = 'N';
    }
    mSeedTypeDef[3] = opts.mAllowGUWobble;
    mSeedTypeDef[4] = opts.mAllowMismatch;

    set_backtrack(mOutputAlign);

    mSiteScores.init_from_args(opts);
}

int PITACore::open_output_file() {
    // Open output file 1
    mOFile1.open(toCString(mOFileDDG), std::ofstream::out);
    if (!mOFile1.good()) {
        std::cerr << "ERROR: Could not open output file " << toCString(mOFileDDG) << std::endl;
        return seqan::ArgumentParser::PARSE_ERROR;
    }

    // Open output file 2
    mOFile2.open(toCString(mOFileTotal), std::ofstream::out);
    if (!mOFile2.good()) {
        std::cerr << "ERROR: Could not open output file " << toCString(mOFileTotal) << std::endl;
        return seqan::ArgumentParser::PARSE_ERROR;
    }

    return 0;
}

int PITACore::calculate_all_scores() {
    int retVal;

    for (unsigned i = 0; i < length(mMiRNASeqs); ++i) {

#if SEQAN_ENABLE_DEBUG
        clock_t startTime = clock();
#endif

        retVal = calculate_mirna_scores(i);
        if (retVal != 0) {
            std::cerr << "ERROR: Score calculation failed for " << toCString((seqan::CharString) mMiRNAIds[i]);
            std::cerr << "." << std::endl;
            return 1;
        }

#if SEQAN_ENABLE_DEBUG
        std::cout << toCString((seqan::CharString) (mMiRNAIds[i])) << ": ";
        std::cout << double(clock() - startTime) / (double) CLOCKS_PER_SEC << " seconds." << std::endl;
#endif

    }

    return 0;
}

int PITACore::calculate_mirna_scores(unsigned pIdx) {
    int retVal;
    mikan::TRNAStr miRNASeq = mMiRNASeqs[pIdx];

    // Generate seed sequences
    PITASeedSeqs seedSeqs;
    seedSeqs.set_mirna_seq(miRNASeq);
    seedSeqs.set_flags(mSeedTypeDef);
    retVal = seedSeqs.create_seed_seqs();
    if (retVal != 0) {
        std::cerr << "ERROR: Generate seed sequences failed." << std::endl;
        return 1;
    }

    // Search seed sites
    if (mExecSearchSeedSites) {
        retVal = mSeedSites.find_seed_sites(seedSeqs, mSeedTypeDef);
        if (retVal != 0) {
            std::cerr << "ERROR: Seed site search failed." << std::endl;
            return 1;
        }
    }

    // Filter overlapped sites
    if (OVERLAP_LEN != 0 && mExecFilterOverlap) {
        retVal = mOverlappedSites.filter_overlapped_sites(mSeedSites, OVERLAP_LEN);
        if (retVal != 0) {
            std::cerr << "ERROR: Check overlapped sites failed." << std::endl;
            return 1;
        }
    }

    // Calculate ddG values
    if (mExecCalSiteScore) {
        retVal = mSiteScores.calc_scores(miRNASeq, mMRNASeqs, mSeedSites);
        if (retVal != 0) {
            std::cerr << "ERROR: Calculate ddG scores failed." << std::endl;
            return 1;
        }
    }

    // Sort target sites
    if (mExecSortSites) {
        retVal = mSortedSites.generate_sorted_mrna_pos(mSeedSites);
        if (retVal != 0) {
            std::cerr << "ERROR: Sort target sites failed." << std::endl;
            return 1;
        }
    }

    // Summarize ddG values
    if (mExecSumScores) {
        const seqan::String<unsigned> &sortedPos = mSortedSites.get_sorted_mrna_pos();
        retVal = mTotalScores.calc_scores(mSeedSites, mSiteScores, sortedPos);
        if (retVal != 0) {
            std::cerr << "ERROR: Calculate total ddG scores failed." << std::endl;
            return 1;
        }
    }

    // Write ddG values
    if (mOutputDDGScore) {
        retVal = write_ddg_score(mMiRNAIds[pIdx]);
        if (retVal != 0) {
            std::cerr << "ERROR: Could not write ddG scores." << std::endl;
            return 1;
        }
    }

    // Write total ddG values
    if (mOutputTotalScore) {
        retVal = write_total_score(mMiRNAIds[pIdx]);
        if (retVal != 0) {
            std::cerr << "ERROR: Could not write total ddG scores." << std::endl;
            return 1;
        }
    }

    // Write alignments
    if (mOutputAlign) {
        retVal = write_alignment(mMiRNAIds[pIdx]);
        if (retVal != 0) {
            std::cerr << "ERROR: Could not write alignments." << std::endl;
            return 1;
        }
    }

    mSeedSites.clear_pos();
    mOverlappedSites.clear_cluster();
    mSiteScores.clear_scores();
    mSortedSites.clear_site_pos();
    mTotalScores.clear_scores();

    return 0;
}

int PITACore::write_ddg_score(seqan::CharString const &pMiRNAId) {
    const seqan::String<unsigned> &mRNAPos = mSeedSites.get_mrna_pos();
    const seqan::String<unsigned> &sitePos = mSeedSites.get_site_pos();
    const seqan::StringSet<seqan::CharString> &seedTypes = mSeedSites.get_seed_types();
    const seqan::String<unsigned> &sortedPos = mSortedSites.get_sorted_mrna_pos();
    seqan::CharString seedType;
    int seedStart = 0;
    int posIdx;
    float score;

    for (unsigned i = 0; i < length(sortedPos); ++i) {
        posIdx = sortedPos[i];
        if (!mSiteScores.mEffectiveSites[posIdx]) {
            continue;
        }

        seedStart = sitePos[posIdx];
        score = mSiteScores.get_score(posIdx);
        score = roundf(score * 100.0f) / 100.0f;

        mOFile1 << toCString(pMiRNAId) << "\t";
        mOFile1 << toCString((seqan::CharString) (mMRNAIds[mRNAPos[posIdx]])) << "\t";
        mOFile1 << seedStart + 1 << "\t";
        mOFile1 << seedStart + 1 + INDEXED_SEQ_LEN << "\t";
        mOFile1 << toCString((seqan::CharString) (seedTypes[posIdx])) << "\t";
        mOFile1 << score << "\t";
        mOFile1 << std::endl;
    }

    return 0;
}

int PITACore::write_total_score(seqan::CharString const &pMiRNAId) {
    const seqan::String<float> &totalScores = mTotalScores.get_scores();
    const seqan::String<int> &mRNAPos = mTotalScores.get_mrna_pos();
    const seqan::String<int> &siteNum = mTotalScores.get_site_num();
    float score;

    for (unsigned i = 0; i < length(mRNAPos); ++i) {
        score = totalScores[i];
        score = roundf(score * 100.0f) / 100.0f;

        mOFile2 << toCString(pMiRNAId) << "\t";
        mOFile2 << toCString((seqan::CharString) (mMRNAIds[mRNAPos[i]])) << "\t";
        mOFile2 << score << "\t";
        mOFile2 << siteNum[i] << "\t";
        mOFile2 << std::endl;
    }

    return 0;
}

int PITACore::write_alignment(seqan::CharString const &pMiRNAId) {
    const seqan::String<unsigned> &mRNAPos = mSeedSites.get_mrna_pos();
    const seqan::String<unsigned> &sitePos = mSeedSites.get_site_pos();
    const seqan::StringSet<seqan::CharString> &seedTypes = mSeedSites.get_seed_types();
    const seqan::String<unsigned> &sortedPos = mSortedSites.get_sorted_mrna_pos();
    seqan::CharString seedType;
    int seedStart = 0;
    int posIdx;
    float score;
    int count = 0;
    float dGduplex;
    float dG5;
    float dG3;
    float dGopen;
    float dG0;
    float dG1;


    for (unsigned i = 0; i < length(sortedPos); ++i) {
        posIdx = sortedPos[i];

        if (!mSiteScores.mEffectiveSites[posIdx]) {
            continue;
        }

        seedStart = sitePos[posIdx];
        score = mSiteScores.get_score(posIdx);
        score = roundf(score * 100.0f) / 100.0f;

        dGduplex = (float) mSiteScores.get_dgall(posIdx);
        dGduplex = roundf(dGduplex * 100.0f) / 100.0f;
        dG5 = (float) mSiteScores.get_dg5(posIdx);
        dG5 = roundf(dG5 * 100.0f) / 100.0f;
        dG3 = (float) mSiteScores.get_dg3(posIdx);
        dG3 = roundf(dG3 * 100.0f) / 100.0f;
        dGopen = (float) mSiteScores.get_dg0(posIdx) - (float) mSiteScores.get_dg1(posIdx);
        dGopen = roundf(dGopen * 100.0f) / 100.0f;
        dG0 = (float) mSiteScores.get_dg0(posIdx);
        dG0 = roundf(dG0 * 100.0f) / 100.0f;
        dG1 = (float) mSiteScores.get_dg1(posIdx);
        dG1 = roundf(dG1 * 100.0f) / 100.0f;

        std::cout << "### " << count + 1 << ": " << toCString(pMiRNAId) << " ###" << std::endl;
        mSiteScores.print_alignment(posIdx);
        std::cout << "  miRNA:               " << toCString(pMiRNAId) << std::endl;
        std::cout << "  mRNA:                " << toCString((seqan::CharString) (mMRNAIds[mRNAPos[posIdx]]));
        std::cout << std::endl;
        std::cout << "  seed type:           " << toCString((seqan::CharString) (seedTypes[posIdx])) << std::endl;
        std::cout << "  position(start):     " << seedStart + 1 << std::endl;
        std::cout << "  position(end):       " << seedStart + 1 + INDEXED_SEQ_LEN << std::endl;
        std::cout << "  ddG:                 " << score << std::endl;
        std::cout << "  dGduplex(dG5 + dG3): " << dGduplex << std::endl;
        std::cout << "  dG5:                 " << dG5 << std::endl;
        std::cout << "  dG3:                 " << dG3 << std::endl;
        std::cout << "  dGopen(dG0 - dG1):   " << dGopen << std::endl;
        std::cout << "  dG0:                 " << dG0 << std::endl;
        std::cout << "  dG1:                 " << dG1 << std::endl;
        std::cout << std::endl;

        ++count;

    }

    return 0;
}

} // namespace ptddg

