#include "mr3_align.hpp"    // MR3Align
#include "dp_core.hpp"      // MR3DPCore
#include "dp_score.hpp"     // MR3DPScore

using namespace seqan;

namespace mr3as {

//
// MR3Align methods
//
void MR3Align::clear_align() {
    clear(mEffectiveSites);
    clear(mAlignMRNA);
    clear(mAlignBars);
    clear(mAlignMiRNA);
    clear(mAlignSeedScores);
    clear(mAlign3PScores);
    clear(mAlignScores);
    clear(mAlignSeedMiRNA);
    clear(mAlignSeedMRNA);
    clear(mAlign3pMRNA);
    clear(mAlign3pMiRNA);
    clear(mGapCountMiRNA);
    clear(mGapCountMRNA);
}

void MR3Align::resize_align(unsigned pSize) {
    resize(mEffectiveSites, pSize, false);
    resize(mAlignMRNA, pSize);
    resize(mAlignBars, pSize);
    resize(mAlignMiRNA, pSize);
    resize(mAlignSeedScores, pSize);
    resize(mAlign3PScores, pSize);
    resize(mAlignScores, pSize);
    resize(mAlignSeedMiRNA, pSize);
    resize(mAlignSeedMRNA, pSize);
    resize(mAlign3pMRNA, pSize);
    resize(mAlign3pMiRNA, pSize);
    resize(mGapCountMiRNA, pSize);
    resize(mGapCountMRNA, pSize);
}

void MR3Align::align_seed(
        int pIdx,
        mikan::TRNAStr &pIMiRNASeedSeq,
        mikan::TRNAStr &pIMRNASeedSeq,
        int pMMpos) {
    int score = 0;
    unsigned idx2 = 0;

    resize(mAlignSeedMiRNA[pIdx], length(pIMRNASeedSeq));
    resize(mAlignSeedMRNA[pIdx], length(pIMRNASeedSeq));
    mGapCountMiRNA[pIdx] = 0;
    mGapCountMRNA[pIdx] = 0;

//    std::cout << "seed score: ";
    for (unsigned i = 0; i < length(pIMRNASeedSeq); ++i) {
        if (pMMpos == -1) {
            idx2 = i;
        } else if (i == length(pIMiRNASeedSeq) - pMMpos - 1) {
            mAlignSeedMiRNA[pIdx][i] = '-';
            mAlignSeedMRNA[pIdx][i] = pIMRNASeedSeq[i];
            score -= (4.0f * mDPScore.gap_open());
            ++mGapCountMiRNA[pIdx];
//            std::cout << score << " (g), ";
            continue;
        }

        mAlignSeedMiRNA[pIdx][i] = pIMiRNASeedSeq[idx2];
        mAlignSeedMRNA[pIdx][i] = pIMRNASeedSeq[i];

        std::string mielm = toCString(CharString(pIMiRNASeedSeq[idx2]));
        std::string melm = toCString(CharString(pIMRNASeedSeq[i]));

        int tscore = mDPScore.score_ab(mielm[0], melm[0]);
        if (i == 0 && tscore < 0) {
            tscore = 0;
        }
        score += 4.0f * tscore;

        if (pMMpos != -1) {
            ++idx2;
        }
//        std::cout << score;
//        std::cout << " (" << mielm[0] << ", " << melm[0] << "), ";
    }
//    std::cout << std::endl;

    mAlignSeedScores[pIdx] = score;
    mAlignScores[pIdx] = score;


}

void MR3Align::init_3p_align(int pIdx) {
    mAlign3PScores[pIdx] = 0;
    resize(mAlign3pMiRNA[pIdx], 0);
    resize(mAlign3pMRNA[pIdx], 0);
    mGapCountMiRNA[pIdx] = 0;
    mGapCountMRNA[pIdx] = 0;
}

void MR3Align::align_3p(int pIdx, seqan::Rna5String &pIMiRNA3pSeq, seqan::Rna5String &pIMRNA3pSeq) {
//    int score;

//    clearClipping(mAign3P);
//    clearGaps(mAign3P);
//    resize(rows(mAign3P), 2);
//    assignSource(row(mAign3P, 0), pIMiRNA3pSeq);
//    assignSource(row(mAign3P, 1), pIMRNA3pSeq);

//    score = localAlignment(mAign3P, mScoreMatrix3P);
//    score -= 140;

//    std::cout << "miRNA: " << pIMiRNA3pSeq << std::endl;
//    std::cout << "mRNA : " << pIMRNA3pSeq << std::endl;
//    std::cout << score << std::endl;
//    std::cout << mAign3P << std::endl;

    std::string miSeq = toCString(seqan::CharString(pIMiRNA3pSeq));
    std::string mSeq = toCString(seqan::CharString(pIMRNA3pSeq));

    mDPCore.run(miSeq, mSeq, mAlignSeedScores[pIdx]);
    mAlignScores[pIdx] = mDPCore.get_max_score();
    mGapCountMiRNA[pIdx] += mDPCore.get_gap_q_count();
    mGapCountMRNA[pIdx] += mDPCore.get_gap_d_count();

//    std::cout << mDPCore.get_max_score() << std::endl;

//    if (score > 0) {
//        mAlign3PScores[pIdx] = score;
//
//        TGap &alignMiRNA = (TGap &) row(mAign3P, 0);
//        TGap &alignMRNA = (TGap &) row(mAign3P, 1);
//
//        resize(mAlign3pMiRNA[pIdx], length(alignMiRNA) - 1);
//        resize(mAlign3pMRNA[pIdx], length(alignMRNA) - 1);
//
//        for (unsigned i = 0; i < length(alignMiRNA) - 1; ++i) {
//            mAlign3pMiRNA[pIdx][i] = alignMiRNA[i + 1];
//            mAlign3pMRNA[pIdx][i] = alignMRNA[i + 1];
//            if (alignMiRNA[i + 1] == '-') {
//                ++mGapCountMiRNA[pIdx];
//            }
//            if (alignMRNA[i + 1] == '-') {
//                ++mGapCountMRNA[pIdx];
//            }
//        }
//    }
}

void MR3Align::combine_alignments(
        int pIdx,
        mikan::TRNAStr const &pMiRNASeq,
        mikan::TRNAStr const &pMRNASeq,
        bool noA1) {
//    int maxlen = (int) length(pMiRNASeq) + mGapCountMiRNA[pIdx];
    int idx2;
//    int idx2_orig;

    std::string& mi3pSeq = mDPCore.get_q_align();
    std::string& m3pSeq = mDPCore.get_d_align();

    unsigned maxlen = length(pMiRNASeq) + mGapCountMiRNA[pIdx];

    resize(mAlignMiRNA[pIdx], maxlen);
    resize(mAlignMRNA[pIdx], maxlen);
    resize(mAlignBars[pIdx], maxlen);

    unsigned n = 0;
    mAlignMiRNA[pIdx][0] = pMiRNASeq[0];
    if (noA1) {
        mAlignMRNA[pIdx][0] = '-';
    } else {
        mAlignMRNA[pIdx][0] = pMRNASeq[0];
    }
    ++n;

    for (unsigned i = 0; i < length(mAlignSeedMiRNA[pIdx]); ++i) {
        idx2 = i + 1;
        mAlignMiRNA[pIdx][idx2] = mAlignSeedMiRNA[pIdx][i];
        mAlignMRNA[pIdx][idx2] = mAlignSeedMRNA[pIdx][i];
        ++n;
    }

    for (unsigned i = 0; i < mi3pSeq.size(); ++i) {
        idx2 = i + static_cast<int>(length(mAlignSeedMiRNA[pIdx])) + 1;
        mAlignMiRNA[pIdx][idx2] = mi3pSeq[i];
        mAlignMRNA[pIdx][idx2] = m3pSeq[i];
        ++n;
    }

    unsigned miIdx = n - mGapCountMiRNA[pIdx];
    unsigned mIdx = n - mGapCountMRNA[pIdx];
    for (unsigned i = 0; i < maxlen - n; ++i) {
        idx2 = i + n;
        mAlignMiRNA[pIdx][idx2] = pMiRNASeq[miIdx + i];
        if (mIdx + i >= length(pMRNASeq)) {
            mAlignMRNA[pIdx][idx2] = '-';
        } else {
            mAlignMRNA[pIdx][idx2] = pMRNASeq[mIdx + i];
        }
    }


//    for (unsigned i = 0; i < length(mAlign3pMiRNA[pIdx]); ++i) {
//        idx2 = i + (int) length(mAlignSeedMiRNA[pIdx]) + 1;
//        mAlignMiRNA[pIdx][idx2] = mAlign3pMiRNA[pIdx][i];
//
//        if (i < length(mAlignMRNA[pIdx]) - 1) {
//            mAlignMRNA[pIdx][idx2] = mAlign3pMRNA[pIdx][i];
//        } else {
//            mAlignMRNA[pIdx][idx2] = '-';
//            ++mGapCountMRNA[pIdx];
//        }
//    }
//
//    idx2 = (int) length(mAlignSeedMiRNA[pIdx]) + (int) length(mAlign3pMiRNA[pIdx]) + 1;
//    idx2_orig = idx2 - mGapCountMiRNA[pIdx];
//    while (idx2 < maxlen) {
//        if (idx2_orig < (int) length(pMiRNASeq)) {
//            mAlignMiRNA[pIdx][idx2] = pMiRNASeq[idx2_orig];
//        } else {
//            mAlignMiRNA[pIdx][idx2] = '-';
//            ++mGapCountMiRNA[pIdx];
//        }
//        ++idx2;
//        ++idx2_orig;
//    }
//
//    idx2 = (int) length(mAlignSeedMiRNA[pIdx]) + (int) length(mAlign3pMiRNA[pIdx]) + 1;
//    idx2_orig = idx2 - mGapCountMRNA[pIdx];
//    while (idx2 < maxlen) {
//        if (idx2_orig < (int) length(pMRNASeq)) {
//            mAlignMRNA[pIdx][idx2] = pMRNASeq[idx2_orig];
//        } else {
//            mAlignMRNA[pIdx][idx2] = '-';
//            ++mGapCountMRNA[pIdx];
//        }
//        ++idx2;
//        ++idx2_orig;
//    }

    set_align_bars(pIdx);

    reverse(mAlignMiRNA[pIdx]);
    reverse(mAlignMRNA[pIdx]);
    reverse(mAlignBars[pIdx]);

//    std::cout <<  mAlignMiRNA[pIdx] << std::endl;
//    std::cout <<  mAlignBars[pIdx] << std::endl;
//    std::cout << mAlignMRNA[pIdx] << std::endl;
}

void MR3Align::set_align_bars(int pIdx) {
    char miRNA, mRNA;

    for (unsigned i = 0; i < length(mAlignBars[pIdx]); ++i) {
        miRNA = mAlignMiRNA[pIdx][i];
        mRNA = mAlignMRNA[pIdx][i];

        if (miRNA == 'A') {
            if (mRNA == 'U') {
                mAlignBars[pIdx][i] = '|';
            } else {
                mAlignBars[pIdx][i] = ' ';
            }
        } else if (miRNA == 'C') {
            if (mRNA == 'G') {
                mAlignBars[pIdx][i] = '|';
            } else {
                mAlignBars[pIdx][i] = ' ';
            }
        } else if (miRNA == 'G') {
            if (mRNA == 'C') {
                mAlignBars[pIdx][i] = '|';
            } else if (mRNA == 'U') {
                mAlignBars[pIdx][i] = ':';
            } else {
                mAlignBars[pIdx][i] = ' ';
            }
        } else if (miRNA == 'U') {
            if (mRNA == 'A') {
                mAlignBars[pIdx][i] = '|';
            } else if (mRNA == 'G') {
                mAlignBars[pIdx][i] = ':';
            } else {
                mAlignBars[pIdx][i] = ' ';
            }
        } else {
            mAlignBars[pIdx][i] = ' ';
        }
    }

}

void MR3Align::get_mrna_seq(int pIdx, seqan::CharString &pStrMRNA) {
    int idx = 0;

    resize(pStrMRNA, length(mAlignMRNA[pIdx]) - mGapCountMRNA[pIdx]);
    for (unsigned i = 0; i < length(mAlignMRNA[pIdx]); ++i) {
        if (mAlignMRNA[pIdx][i] != '-' || i == length(mAlignMRNA[pIdx]) - 1) {
            pStrMRNA[idx] = mAlignMRNA[pIdx][i];
            ++idx;
        }
    }

    resize(pStrMRNA, idx);
    reverse(pStrMRNA);
}

} // namespace mr3as
