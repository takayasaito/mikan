#ifndef TS5_SEED_SITE_HPP_
#define TS5_SEED_SITE_HPP_

#include <seqan/sequence.h>
#include <seqan/index.h>
#include "mk_typedef.hpp"        // TRNATYPE, TCharSet, TRNASet, TIndexQGram, TFinder
#include "mk_seed_seq.hpp"       // MKSeedSeqs
#include "mk_seed_site.hpp"      // MKSeedSites
#include "mk_option.hpp"         // MKOptions

namespace ts5cs {

//
// Generate miRNA seeds
//
class TS5SeedSeqs : public mikan::MKSeedSeqs {
public:
    // Define methods
    TS5SeedSeqs(mikan::MKOptions const &opts) : MKSeedSeqs(opts) {
        set_flags();
    }

    // Method prototype
    void set_flags();
};

//
// miRNA seed sites
//
class TS5SeedSites : public mikan::MKSeedSites {
public:
    // Define methods
    TS5SeedSites(mikan::TIndexQGram &pRNAIdx, mikan::TFinder &pFinder, mikan::TRNASet const &pMRNASeqs) :
            MKSeedSites(pRNAIdx, pFinder, pMRNASeqs) {
        mMinToCDS = 14;
    }

private:
    virtual bool set_new_seed_type(unsigned pMRNAPos, unsigned pSitePos,
                                   mikan::TRNAStr &pMiRNASeq, mikan::TCharSet &pSeedTypeDef,
                                   seqan::CharString &pSeedType, int pMisMatchPos, bool pEffectiveSite);

};

} // namespace ts5cs

#endif /* TS5_SEED_SITE_HPP_ */
