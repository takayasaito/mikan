#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_pita.hpp"

namespace {

class Site05BT2 : public TestSitePITA {
protected:
    Site05BT2() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "ts_05_bt_2.fasta";

        resize(mSeedDef, 6);
        mSeedDef[0] = 'Y';
        mSeedDef[1] = 'Y';
        mSeedDef[2] = 'Y';
        mSeedDef[3] = "0";
        mSeedDef[4] = "0:0";
        mSeedDef[5] = "1";
    }

};

TEST_F(Site05BT2, mir1_bt) {
    create_seed_seqs(1);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(0u, sites.get_length());
}

TEST_F(Site05BT2, mir1_def) {
    mSeedDef[3] = "1";
    mSeedDef[4] = "0:1";
    mSeedDef[5] = "1";
    create_seed_seqs(1);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(17u, sites.get_length());

//    test_sites(sites, 0, "GUT", 5, 25, false, 0);

    test_sites(sites, 0, "8mer_GUT", 10, 24, true, 4);

    test_sites(sites, 1, "8mer_GUT", 24, 24, true, 5);

//    test_sites(sites, 3, "MM", 0, 25, false, 0);
//    test_sites(sites, 4, "MM", 1, 25, false, 0);
//    test_sites(sites, 5, "MM", 2, 25, false, 0);
//    test_sites(sites, 6, "MM", 3, 25, false, 0);
//    test_sites(sites, 7, "MM", 4, 25, false, 0);

//    test_sites(sites, 8, "MM", 16, 24, false, 0);
    test_sites(sites, 2, "8mer_MM", 17, 24, true, 4);
    test_sites(sites, 3, "8mer_MM", 18, 24, true, 4);
    test_sites(sites, 4, "8mer_MM", 19, 24, true, 4);

//    test_sites(sites, 12, "MM", 20, 24, false, 0);
    test_sites(sites, 5, "8mer_MM", 21, 24, true, 5);
    test_sites(sites, 6, "8mer_MM", 22, 24, true, 5);
    test_sites(sites, 7, "8mer_MM", 23, 24, true, 5);

//    test_sites(sites, 16, "MMGU", 11, 26, false, 0);
//    test_sites(sites, 17, "MMGU", 12, 26, false, 0);

//    test_sites(sites, 18, "MMGU", 9, 25, false, 0);

//    test_sites(sites, 19, "MMGU", 6, 24, false, 0);
    test_sites(sites, 8, "8mer_MMGU", 7, 24, true, 2);
    test_sites(sites, 9, "8mer_MMGU", 8, 24, true, 2);
    test_sites(sites, 10, "8mer_MMGU", 9, 24, true, 2);

//    test_sites(sites, 23, "MMGU", 0, 24, false, 0);
//    test_sites(sites, 24, "MMGU", 1, 24, false, 0);
    test_sites(sites, 11, "8mer_MMGU", 2, 24, true, 2);
    test_sites(sites, 12, "8mer_MMGU", 3, 24, true, 2);

    test_sites(sites, 13, "8mer_MMGU", 14, 24, true, 3);
    test_sites(sites, 14, "8mer_MMGU", 15, 24, true, 3);

//    test_sites(sites, 29, "MMGU", 11, 24, false, 0);
    test_sites(sites, 15, "8mer_MMGU", 12, 24, true, 3);
    test_sites(sites, 16, "8mer_MMGU", 13, 24, true, 3);
}

}
