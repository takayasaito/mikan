#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_rh2.hpp"

namespace {

class Site05BT1 : public TestSiteRH2 {
protected:
    Site05BT1() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "ts_05_bt_1.fasta";
        O1FNAME1 = (char *) "test_output1_site_1.txt";
        O1FNAME2 = (char *) "test_output1_mrna_1.txt";
        O2FNAME1 = (char *) "test_output2_site_1.txt";
        O2FNAME2 = (char *) "test_output2_mrna_1.txt";
        OMPATH = (char *) "mk_rh2/";

        resize(mSeedDef, 1);
        mSeedDef[0] = "6mer";
        mOverlapDef = "orig";
    }

    typedef mikan::TIndexQGram TIdx;
    typedef mikan::TFinder TFin;
    typedef rh2mfe::RH2SeedSites TSit;

};

TEST_F(Site05BT1, mir124_bt) {
    read_files();
    set_seqs();
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);

    int ret_val = sites.find_seed_sites(mirna_seqs[0], mSeedDef);
    EXPECT_EQ(0, ret_val);
    EXPECT_EQ(0u, sites.get_length());
}

TEST_F(Site05BT1, mir124_def) {
    read_files();
    set_seqs();
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);

    mSeedDef[0] = "7mGU+";
    int ret_val = sites.find_seed_sites(mirna_seqs[0], mSeedDef);
    EXPECT_EQ(0, ret_val);
    EXPECT_EQ(0u, sites.get_length());
}

}
