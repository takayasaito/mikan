#include <pita_inst_template.hpp> // TRNATYPE
#include <pita_score.hpp>         // PITADDGScores, PITATotalScores

using namespace seqan;

namespace ptddg {

//
// PITAAlign methods
//
template<class TRNAString>
void PITAAlign<TRNAString>::clear_align() {
    clear(mEffectiveSites);
    clear(mAlignMRNA);
    clear(mAlignBars);
    clear(mAlignMiRNA);
}

template<class TRNAString>
void PITAAlign<TRNAString>::resize_align(unsigned pSize) {
    resize(mEffectiveSites, pSize, false);
    resize(mAlignMRNA, pSize);
    resize(mAlignBars, pSize);
    resize(mAlignMiRNA, pSize);
}

template<class TRNAString>
void PITAAlign<TRNAString>::create_align(
        int pId,
        TRNAString const &pMiRNASeq,
        TRNAString const &pMRNASeq,
        CharString const &pSeedType,
        unsigned pSitePos,
        int) {
    int seedLen = lexicalCast<int>(pSeedType[0]);
    int startPos;
    int pos;
    char mChar;


    resize(mAlignMiRNA[pId], length(pMiRNASeq));
    for (unsigned i = 0; i < length(pMiRNASeq); ++i) {
        mAlignMiRNA[pId][length(pMiRNASeq) - i - 1] = pMiRNASeq[i];
    }

    resize(mAlignMRNA[pId], length(pMiRNASeq), ' ');
    startPos = pSitePos + (INDEXED_SEQ_LEN + 1) - (int) length(pMiRNASeq);
    for (unsigned i = 0; i < length(pMiRNASeq); ++i) {
        if (startPos + (int) i > 0) {
            mAlignMRNA[pId][i] = pMRNASeq[startPos + i];
        }
    }

    resize(mAlignBars[pId], length(pMiRNASeq), ' ');
    for (int i = 1; i < seedLen + 1; ++i) {
        pos = (int) length(pMiRNASeq) - 1 - i;
        mChar = ' ';
        if ((mAlignMiRNA[pId][pos] == 'C' && mAlignMRNA[pId][pos] == 'G')
            || (mAlignMiRNA[pId][pos] == 'G' && mAlignMRNA[pId][pos] == 'C')
            || (mAlignMiRNA[pId][pos] == 'A' && mAlignMRNA[pId][pos] == 'U')
            || (mAlignMiRNA[pId][pos] == 'U' && mAlignMRNA[pId][pos] == 'A')) {
            mChar = '|';
        } else if ((mAlignMiRNA[pId][pos] == 'G' && mAlignMRNA[pId][pos] == 'U')
                   || (mAlignMiRNA[pId][pos] == 'U' && mAlignMRNA[pId][pos] == 'G')) {
            mChar = ':';
        }

        mAlignBars[pId][pos] = mChar;
    }

}

//
// PITADGDuplexScores methods
//

template<class TRNAString>
void PITADGDuplexScores<TRNAString>::clear_scores() {
    clear(mEffectiveSites);
}

template<class TRNAString>
int PITADGDuplexScores<TRNAString>::calc_scores(
        PITASeedSites<TRNAString> &pSeedSites,
        TRNAString const &pMiRNASeq,
        TRNASet const &pMRNASeqs) {
    const String<unsigned> &mRNAPos = pSeedSites.get_mrna_pos();
    const String<unsigned> &sitePos = pSeedSites.get_site_pos();
    StringSet<CharString> const &seedTypes = pSeedSites.get_seed_types();
    String<int> const &mismatchPos = pSeedSites.get_mismatched_pos();
    std::string inputMiRNASeq;
    std::string inputMRNASeq;
    std::vector<int> inputMatchSeq;
    int seqStart = 0;
    int seqEnd = 0;

    resize(mEffectiveSites, length(pSeedSites.mEffectiveSites));
    mVRws.preppare_duplexfold((int) length(pSeedSites.mEffectiveSites));

    inputMiRNASeq.resize(length(pMiRNASeq));
    create_input_mirna_seq(pMiRNASeq, inputMiRNASeq);

    inputMRNASeq.resize(TARGET_SEQ_LEN);

    for (unsigned i = 0; i < length(mRNAPos); ++i) {
        if (!pSeedSites.mEffectiveSites[i]) {
            mEffectiveSites[i] = false;
            continue;
        }

        seqEnd = sitePos[i] + (INDEXED_SEQ_LEN + 1);
        seqStart = seqEnd - TARGET_SEQ_LEN;
        if (seqStart < 0) {
            seqStart = 0;
        }

        create_input_mrna_seq(pMRNASeqs[mRNAPos[i]], seqStart, seqEnd, inputMRNASeq);
        create_input_matched_seq(seedTypes[i], mismatchPos[i], inputMatchSeq);
//        print_input(seedTypes[i], inputMiRNASeq, inputMRNASeq, inputMatchSeq);

        mVRws.duplexfold(i, inputMiRNASeq, inputMRNASeq, inputMatchSeq, inputMatchSeq);
//        mVRws.print_duplexfold_ret_vals(i);

        mAlign.create_align(i, pMiRNASeq, pMRNASeqs[mRNAPos[i]], seedTypes[i], (unsigned) sitePos[i],
                            mismatchPos[i]);

        mEffectiveSites[i] = true;
    }

    return 0;
}

template<class TRNAString>
void PITADGDuplexScores<TRNAString>::create_input_mirna_seq(
        TRNAString const &pMiRNASeq,
        std::string &pInputMiRNASeq) {
    for (unsigned i = 0; i < length(pMiRNASeq); ++i) {
        pInputMiRNASeq[i] = pMiRNASeq[i];
    }
}

template<class TRNAString>
void PITADGDuplexScores<TRNAString>::create_input_mrna_seq(
        TRNAString const &pMRNASeq,
        int pStart,
        int pEnd,
        std::string &pInputMRNASeq) {
    int seqStartPos = TARGET_SEQ_LEN - (pEnd - pStart);

    for (int i = 0; i < seqStartPos; ++i) {
        pInputMRNASeq[i] = 'A';
    }

    for (int i = 0; i < (pEnd - pStart); ++i) {
        pInputMRNASeq[seqStartPos + i] = pMRNASeq[pStart + i];
    }

}

template<class TRNAString>
void PITADGDuplexScores<TRNAString>::create_input_matched_seq(
        CharString const &pSeedType,
        int pMismatchPos,
        std::vector<int> &pInputMatchSeq) {
    unsigned seedLen = lexicalCast<unsigned>(pSeedType[0]);
    pInputMatchSeq.resize((seedLen + 1));

    for (int i = 0; i < (int) seedLen + 1; ++i) {
        if (i == 0) {
            pInputMatchSeq[i] = 0;
        } else {
            pInputMatchSeq[i] = 1 + i;
        }
    }

    if (pSeedType == "8mer_MM" || pSeedType == "7mer_MM" || pSeedType == "8mer_MMGU" || pSeedType == "7mer_MMGU") {
        pInputMatchSeq[INDEXED_SEQ_LEN - pMismatchPos] = 0;
    }

}

template<class TRNAString>
void PITADGDuplexScores<TRNAString>::print_input(
        CharString const &pSeedType,
        std::string &pInputMiRNASeq,
        std::string &pInputMRNASeq,
        std::vector<int> &pInputMatchSeq) {
    std::cout << "seed type:   " << toCString(pSeedType) << std::endl;
    std::cout << "miRNA seq:   " << pInputMiRNASeq << std::endl;
    std::cout << "mRNA seq:    " << pInputMRNASeq << std::endl;
    std::cout << "constraints: ";
    for (unsigned k = 0; k < pInputMatchSeq.size(); ++k) {
        std::cout << pInputMatchSeq[k];
        if (k != pInputMatchSeq.size() - 1) {
            std::cout << ",";
        } else {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

//
// PITADGOpenScores methods
//

template<class TRNAString>
void PITADGOpenScores<TRNAString>::clear_scores() {
    clear(mEffectiveSites);
}

template<class TRNAString>
int PITADGOpenScores<TRNAString>::calc_scores(
        PITASeedSites<TRNAString> &pSeedSites,
        TRNASet const &pMRNASeqs,
        int pFlankUp,
        int pFlankDown) {
    const String<unsigned> &mRNAPos = pSeedSites.get_mrna_pos();
    const String<unsigned> &sitePos = pSeedSites.get_site_pos();
    std::string inputMRNASeq;
    int seqStart = 0;
    int seqEnd = 0;
    int seqStart2, seqEnd2;
    int paramU, paramS, paramFT;
    int seqLen;

    resize(mEffectiveSites, length(pSeedSites.mEffectiveSites));

    paramU = pFlankUp;
    paramS = DDG_OPEN + DDG_AREA + pFlankDown - 1;
    paramFT = DDG_OPEN + pFlankDown;
    mVRws.prepare_ddg4((int) length(pSeedSites.mEffectiveSites), paramU, paramS, paramFT, paramFT);

    seqLen = DDG_OPEN + DDG_AREA * 2 + pFlankUp + pFlankDown;
    resize(inputMRNASeq, seqLen);

    for (unsigned i = 0; i < length(mRNAPos); ++i) {
        if (!pSeedSites.mEffectiveSites[i]) {
            mEffectiveSites[i] = false;
            continue;
        }

        seqEnd = sitePos[i] + (INDEXED_SEQ_LEN + 1);
        seqStart = seqEnd - DDG_OPEN;
        seqStart2 = seqStart - (DDG_AREA + pFlankDown);
        seqEnd2 = seqEnd + (DDG_AREA + pFlankUp);

        create_input_mrna_seq(pMRNASeqs[mRNAPos[i]], seqStart2, seqEnd2, inputMRNASeq);
//        print_input(inputMRNASeq);

        mVRws.calc_ddg4(i, inputMRNASeq);
//        mVRws.print_ddg4_ret_vals(i);

        mEffectiveSites[i] = true;

    }

    return 0;
}

template<class TRNAString>
void PITADGOpenScores<TRNAString>::create_input_mrna_seq(
        TRNAString const &pMRNASeq,
        int pStart,
        int pEnd,
        std::string &pInputMRNASeq) {
    int k = 0;
    for (int i = pStart; i < pEnd; ++i) {
        if ((i < 0) || (i >= (int) length(pMRNASeq))) {
            pInputMRNASeq[k] = 'A';
        } else {
            pInputMRNASeq[k] = pMRNASeq[i];
        }
        ++k;
    }
}

template<class TRNAString>
void PITADGOpenScores<TRNAString>::print_input(std::string &pInputMRNASeq) {
    std::cout << "mRNA seq: " << pInputMRNASeq << std::endl;
}

//
// PITADDGScores methods
//

template<class TRNAString>
void PITADDGScores<TRNAString>::clear_scores() {
    clear(mEffectiveSites);
    clear(mDDGScores);
    mDGDuplexScores.clear_scores();
    mDGOpenScores.clear_scores();
    mAlign.clear_align();
}

template<class TRNAString>
int PITADDGScores<TRNAString>::calc_scores(
        PITASeedSites<TRNAString> &pSeedSites,
        TRNAString const &miRNASeq,
        TRNASet const &pMRNASeqs,
        int pFlankUp,
        int pFlankDown) {
    const String<unsigned> &mRNAPos = pSeedSites.get_mrna_pos();

    resize(mEffectiveSites, length(pSeedSites.mEffectiveSites));
    resize(mDDGScores, length(pSeedSites.mEffectiveSites));
    mAlign.resize_align((int) length(pSeedSites.mEffectiveSites));

    mDGDuplexScores.calc_scores(pSeedSites, miRNASeq, pMRNASeqs);
    mDGOpenScores.calc_scores(pSeedSites, pMRNASeqs, pFlankUp, pFlankDown);

    for (unsigned i = 0; i < length(mRNAPos); ++i) {
        if (!pSeedSites.mEffectiveSites[i] || !mDGDuplexScores.mEffectiveSites[i] ||
            !mDGOpenScores.mEffectiveSites[i]) {
            mEffectiveSites[i] = false;
            mDDGScores[i] = 0.0;
            continue;
        }

        mDDGScores[i] = mVRws.get_dgall(i) + (mVRws.get_dg1(i) - mVRws.get_dg0(i));
        mEffectiveSites[i] = true;

    }

    return 0;
}

template<class TRNAString>
void PITADDGScores<TRNAString>::print_alignment(int pIdx) {
    std::stringstream stream;

    stream << "mRNA   5' " << mAlign.mAlignMRNA[pIdx] << " 3'";
    stream << std::endl;
    stream << "          " << mAlign.mAlignBars[pIdx] << "   ";
    stream << std::endl;
    stream << "miRNA  3' " << mAlign.mAlignMiRNA[pIdx] << " 5'";
    stream << std::endl;


    std::cout << stream.str();
}

//
// PITATotalScores methods
//
template<class TRNAString>
void PITATotalScores<TRNAString>::clear_scores() {
    clear(mMRNAPos);
    clear(mSiteNum);
    clear(mTotalScores);
}

template<class TRNAString>
int PITATotalScores<TRNAString>::calc_scores(
        PITASeedSites<TRNAString> &pSeedSites,
        PITADDGScores<TRNAString> &pMFEScores,
        const seqan::String<unsigned> &pSortedSites) {

    const String<unsigned> &siteMRNAPos = pSeedSites.get_mrna_pos();
    int prevPos = -1;
    int newIdx = -1;
    String<int> newIdices;
    unsigned posIdx;
    String<double> maxScores;
    String<int> maxScoreIds;
    String<bool> maxScoreProcessed;
    double score;
    double exp_diff;

    resize(newIdices, length(siteMRNAPos));
    for (unsigned i = 0; i < length(pSortedSites); ++i) {
        posIdx = (unsigned) pSortedSites[i];

        if (!pMFEScores.mEffectiveSites[posIdx]) {
            continue;
        }

        if (prevPos != (int) siteMRNAPos[posIdx]) {
            ++newIdx;
        }
        newIdices[i] = newIdx;
        prevPos = (int) siteMRNAPos[posIdx];
    }

    resize(mTotalScores, newIdx + 1, 0.0);
    resize(mMRNAPos, newIdx + 1);
    resize(mSiteNum, newIdx + 1, 0);
    resize(maxScores, newIdx + 1);
    resize(maxScoreIds, newIdx + 1);
    resize(maxScoreProcessed, newIdx + 1, false);

    for (unsigned i = 0; i < length(pSortedSites); ++i) {
        posIdx = (unsigned) pSortedSites[i];

        if (!pMFEScores.mEffectiveSites[posIdx]) {
            continue;
        }

        score = -1.0 * pMFEScores.get_score(posIdx);
//        score = roundf(score * 100.0) / 100.0;
        if (!maxScoreProcessed[newIdices[i]] || score > maxScores[newIdices[i]]) {
            maxScores[newIdices[i]] = score;
            maxScoreIds[newIdices[i]] = i;
            if (!maxScoreProcessed[newIdices[i]]) {
                maxScoreProcessed[newIdices[i]] = true;
                mTotalScores[newIdices[i]] = 1.0;
                mSiteNum[newIdices[i]] = 1;
                mMRNAPos[newIdices[i]] = siteMRNAPos[posIdx];
            }
        }
    }


    for (unsigned i = 0; i < length(pSortedSites); ++i) {
        posIdx = (unsigned) pSortedSites[i];

        if (!pMFEScores.mEffectiveSites[posIdx] || maxScoreIds[newIdices[i]] == (int) i) {
            continue;
        }

        score = -1.0 * pMFEScores.get_score(posIdx);
//        score = roundf(score * 100.0) / 100.0;
        exp_diff = score - maxScores[newIdices[i]];
        if (exp_diff > MIN_EXP_DIFF) {
            mTotalScores[newIdices[i]] += std::exp(exp_diff);
        }

        mSiteNum[newIdices[i]] += 1;
    }

    for (unsigned i = 0; i < length(mTotalScores); ++i) {
        mTotalScores[i] = -1.0 * (maxScores[i] + std::log(mTotalScores[i]));
    }

    return 0;
}

// Explicit template instantiation
template
class PITAAlign<TRNATYPE>;

template
class PITADGDuplexScores<TRNATYPE>;

template
class PITADGOpenScores<TRNATYPE>;

template
class PITADDGScores<TRNATYPE>;

template
class PITATotalScores<TRNATYPE>;

} // namespace ptddg
