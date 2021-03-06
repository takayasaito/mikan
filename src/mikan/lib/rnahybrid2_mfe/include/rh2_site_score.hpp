#ifndef RH2_SITE_SCORE_HPP_
#define RH2_SITE_SCORE_HPP_

#include <vector>
#include <sstream>
#include <seqan/sequence.h>
#include "mk_typedef.hpp"         // TRNATYPE, TCharSet, TRNASet, TIndexQGram, TFinder
#include "mk_site_score.hpp"      // MKSiteScores
#include "mk_rna_sites.hpp"       // MKRMAWithSites
#include "rh2_option.hpp"         // RH2Options
#include "rh2_seed_site.hpp"      // RH2SeedSites
#include "hybrid_core.hpp"        // RH2WorkSpace, RH2RetValues

namespace rh2mfe {

//
// Store MFE scores
//
class RH2SiteScores : public mikan::MKSiteScores {
public:
    // Define methods
    explicit RH2SiteScores(mikan::MKOptions const &opts) :
            MKSiteScores(opts),
            mMaxMRNALen(opts.mTargetLen),
            mMaxMiRNALen(opts.mQueryLen),
            mRHCore(opts.mTargetLen, opts.mQueryLen, opts.mSeedDef) {

        resize(mScoreTypes, 2);
        mScoreTypes[0] = "mfe";
        mScoreTypes[1] = "nrm";

        init_from_args();

    }

    virtual float get_score(int i) { return mMFEScores[i]; }

    virtual float get_score(int pTypeIdx, int pIdx) {
        if (pTypeIdx == 1) {
            return mNormScores[pIdx];
        }

        return mMFEScores[pIdx];
    }

    float get_norm_score(int i) { return mNormScores[i]; }

    virtual int get_wide_site_start(int pIdx) { return mRHRetVals[pIdx].mTargetPos0; }

    virtual int get_wide_site_length(int pIdx) { return mRHRetVals[pIdx].mHitLen; }

    // Method prototype
    void init_from_args();

    virtual void clear_scores();

    virtual int calc_scores(mikan::TRNAStr const &pMiRNASeq, mikan::TRNASet const &pMRNASeqs,
                            mikan::MKSeedSites &pSeedSites, mikan::MKRMAWithSites &pRNAWithSites);

    void calc_normalized_score(int pIdx, int pTargetLen, int pQueryLen);

    void write_alignment(int pIdx, bool align_only = true);

private:
    int mMaxMRNALen;
    int mMaxMiRNALen;
    seqan::String<float> mMFEScores;
    seqan::String<float> mNormScores;
    rh2::RH2WorkSpace mRHCore;
    std::vector<rh2::RH2RetValues> mRHRetVals;
    seqan::CharString mOverlapDef;

private:
    void create_rh_seq(mikan::TRNAStr const &pRNASeq, std::vector<char> &pRHSeq);

    void write_seq_info(mikan::TRNAStr &pMiSeq, mikan::TRNAStr &pMRNASeq, std::vector<char> &pRhMiRNASeq,
                        std::vector<char> &pRhMRNASeq);
};

} // namespace rh2mfe

#endif /* RH2_SITE_SCORE_HPP_ */
