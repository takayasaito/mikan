#ifndef PITA_CORE_HPP_
#define PITA_CORE_HPP_

#include "mk_typedef.hpp"         // TRNATYPE
#include "pita_option.hpp"        // PITAOptions
#include "pita_score.hpp"         // PITAGGDScores, PITATotalScores
#include "pita_seed_site.hpp"     // PITASeedSites
#include "pita_site_cluster.hpp"  // PITAOverlap, PITASortedSitePos
#include "mk_sequence.hpp"        // MKSequences
#include <seqan/sequence.h>

namespace ptddg {

int PITACoreMain(int argc, char const **argv);

//
// PITA score process core
//
template<class TRNAString, int SEEDLEN = 6>
class PITACore {
public:
    // Define types
    typedef seqan::StringSet<seqan::CharString> TCharSet;
    typedef seqan::StringSet<TRNAString> TRNASet;
    typedef seqan::Index<TRNASet, seqan::IndexQGram<seqan::UngappedShape<SEEDLEN> > > TIndexQGram;
    typedef seqan::Finder<TIndexQGram> TFinder;

    // Constant values
    static const unsigned INDEXED_SEQ_LEN = SEEDLEN;
    static const unsigned OVERLAP_LEN = 0;

    // Declare variables
    bool mExecSearchSeedSites;
    bool mExecCalDDGScore;
    bool mExecFilterOverlap;
    bool mExecSortSites;
    bool mExecSumScores;
    bool mOutputDDGScore;
    bool mOutputTotalScore;
    bool mOutputAlign;
    seqan::CharString mOFileDDG;
    seqan::CharString mOFileTotal;
    int mMinSeedLen;
    int mMaxSeedLen;
    int mFlankUp;
    int mFlankDown;

    seqan::StringSet<seqan::CharString> mSeedDef;

public:
    // Define methods
    PITACore(TCharSet const &pMiRNAIds, TRNASet const &pMiRNASeqs, TCharSet const &pMRNAIds,
             TRNASet const &pMRNASeqs,
             TIndexQGram &pRNAIdx, TFinder &pFinder) :
            mExecSearchSeedSites(true), mExecCalDDGScore(true), mExecFilterOverlap(true),
            mExecSortSites(true), mExecSumScores(true), mOutputDDGScore(true), mOutputTotalScore(true),
            mOutputAlign(true), mMinSeedLen(6), mMaxSeedLen(8), mFlankUp(0), mFlankDown(0),
            mMiRNAIds(pMiRNAIds), mMiRNASeqs(pMiRNASeqs), mMRNAIds(pMRNAIds),
            mMRNASeqs(pMRNASeqs), mSeedSites(pRNAIdx, pFinder, pMRNASeqs),
            mDDGScores() {}

    void set_backtrack(bool pBT) { mDDGScores.set_backtrack(pBT); }

    // Method prototypes
    void init_from_args(PITAOptions &opts);

    int open_output_file();

    int calculate_all_scores();

    int calculate_mirna_scores(unsigned pIdx);

private:
    TCharSet const &mMiRNAIds;
    TRNASet const &mMiRNASeqs;
    TCharSet const &mMRNAIds;
    TRNASet const &mMRNASeqs;

    std::ofstream mOFile1;
    std::ofstream mOFile2;

    PITASeedSites <TRNAString> mSeedSites;
    PITADDGScores <TRNAString> mDDGScores;
    PITAOverlap <TRNAString> mOverlappedSites;
    PITASortedSitePos <TRNAString> mSortedSites;
    PITATotalScores <TRNAString> mTotalScores;

private:
    int write_ddg_score(seqan::CharString const &pMiRNAId);

    int write_total_score(seqan::CharString const &pMiRNAId);

    int write_alignment(seqan::CharString const &pMiRNAId);

};

} // namespace ptddg

#endif /* PITA_CORE_HPP_ */
