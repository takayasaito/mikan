#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_tm1.hpp"

namespace {

class Site01Nmer2 : public TestSiteTM1 {
protected:
    Site01Nmer2() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "ts_01_nmer_2.fasta";
        O1FNAME1 = (char *) "test_output1_site_1.txt";
        O1FNAME2 = (char *) "test_output1_mrna_1.txt";
        O2FNAME1 = (char *) "test_output2_site_1.txt";
        O2FNAME2 = (char *) "test_output2_mrna_1.txt";
        OMPATH = (char *) "mk_tm1/";
    }

    typedef mikan::TIndexQGram TIdx;
    typedef mikan::TFinder TFin;
    typedef tm1p::TM1SeedSites TSit;
    typedef tm1p::TM1SeedSeqs TSeed;

};

TEST_F(Site01Nmer2, mir1) {
    read_files();
    set_seqs();
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);

    TSeed seedSeqs;
    seedSeqs.set_flags(mSeedDef);
    seedSeqs.create_seed_seqs(mirna_seqs[1]);

    int ret_val = sites.find_seed_sites(seedSeqs, mSeedDef);
    EXPECT_EQ(0, ret_val);
    EXPECT_EQ(5u, sites.get_length());

    test_sites2(sites, 0, "6mer", 0, 25, true);
    test_sites2(sites, 1, "7mer-A1", 1, 25, true);
    test_sites2(sites, 2, "7mer-m8", 2, 25, true);
    test_sites2(sites, 3, "8mer", 3, 25, true);
    test_sites2(sites, 4, "7mer-m8", 4, 25, true);
}

}
