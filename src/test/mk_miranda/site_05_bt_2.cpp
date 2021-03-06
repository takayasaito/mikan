#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_miranda.hpp"

namespace {

class Site05BT2 : public TestSiteMR3AS {
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

    EXPECT_EQ(25u, sites.get_length());

//    test_sites(sites, 0, "BT", 20, 23, false, 0);
//    test_sites(sites, 1, "BT", 21, 23, false, 0);
//    test_sites(sites, 2, "BT", 22, 23, false, 0);
//    test_sites(sites, 3, "BT", 23, 23, false, 0);
//    test_sites(sites, 4, "BT", 24, 23, false, 0);

    test_sites(sites, 0, "7mer_BT", 0, 24, true, 1);
    test_sites(sites, 1, "7mer_BT", 1, 24, true, 1);
    test_sites(sites, 2, "8mer_BT", 2, 24, true, 1);
    test_sites(sites, 3, "8mer_BT", 3, 24, true, 1);
    test_sites(sites, 4, "7mer_BT", 4, 24, true, 1);
    test_sites(sites, 5, "7mer_BT", 5, 24, true, 1);

    test_sites(sites, 6, "7mer_BT", 6, 24, true, 2);
    test_sites(sites, 7, "8mer_BT", 7, 24, true, 2);
    test_sites(sites, 8, "8mer_BT", 8, 24, true, 2);
    test_sites(sites, 9, "8mer_BT", 9, 24, true, 2);
    test_sites(sites, 10, "8mer_BT", 10, 24, true, 2);

    test_sites(sites, 11, "7mer_BT", 11, 24, true, 3);
    test_sites(sites, 12, "8mer_BT", 12, 24, true, 3);
    test_sites(sites, 13, "8mer_BT", 13, 24, true, 3);
    test_sites(sites, 14, "8mer_BT", 14, 24, true, 3);
    test_sites(sites, 15, "8mer_BT", 15, 24, true, 3);

    test_sites(sites, 16, "7mer_BT", 16, 24, true, 4);
    test_sites(sites, 17, "8mer_BT", 17, 24, true, 4);
    test_sites(sites, 18, "8mer_BT", 18, 24, true, 4);
    test_sites(sites, 19, "8mer_BT", 19, 24, true, 4);

    test_sites(sites, 20, "7mer_BT", 20, 24, true, 5);
    test_sites(sites, 21, "8mer_BT", 21, 24, true, 5);
    test_sites(sites, 22, "8mer_BT", 22, 24, true, 5);
    test_sites(sites, 23, "8mer_BT", 23, 24, true, 5);
    test_sites(sites, 24, "8mer_BT", 24, 24, true, 5);

}

TEST_F(Site05BT2, mir1_def) {
    mSeedDef[3] = "+";
    mSeedDef[4] = "1:1";
    mSeedDef[5] = "1";
    create_seed_seqs(1);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(74u, sites.get_length());

    test_sites(sites, 0, "7mer_MMGU", 5, 25, true, -1);

    test_sites(sites, 1, "8mer_GUT", 10, 24, true, 4);
    test_sites(sites, 2, "8mer_GUT", 24, 24, true, 5);

    test_sites(sites, 3, "7mer_GU+", 0, 15, true, 0);
    test_sites(sites, 4, "7mer_GU+", 1, 15, true, 0);
    test_sites(sites, 5, "7mer_GU+", 2, 15, true, 0);
    test_sites(sites, 6, "7mer_GU+", 3, 15, true, 0);
    test_sites(sites, 7, "7mer_GU+", 4, 15, true, 0);
    test_sites(sites, 8, "7mer_GU+", 5, 15, true, 0);
    test_sites(sites, 9, "7mer_GU+", 6, 15, true, 0);
    test_sites(sites, 10, "7mer_GU+", 7, 15, true, 0);
    test_sites(sites, 11, "7mer_GU+", 8, 15, true, 0);
    test_sites(sites, 12, "7mer_GU+", 9, 15, true, 0);
    test_sites(sites, 13, "7mer_GU+", 10, 15, true, 0);
    test_sites(sites, 14, "7mer_GU+", 11, 15, true, 0);
    test_sites(sites, 15, "7mer_GU+", 12, 15, true, 0);
    test_sites(sites, 16, "7mer_GU+", 13, 15, true, 0);
    test_sites(sites, 17, "7mer_GU+", 14, 15, true, 0);
    test_sites(sites, 18, "7mer_GU+", 15, 15, true, 0);
    test_sites(sites, 19, "7mer_GU+", 16, 15, true, 0);
    test_sites(sites, 20, "7mer_GU+", 17, 15, true, 0);
    test_sites(sites, 21, "7mer_GU+", 18, 15, true, 0);
    test_sites(sites, 22, "7mer_GU+", 19, 15, true, 0);
    test_sites(sites, 23, "7mer_GU+", 20, 15, true, 0);
    test_sites(sites, 24, "7mer_GU+", 21, 15, true, 0);
    test_sites(sites, 25, "7mer_GU+", 22, 15, true, 0);
    test_sites(sites, 26, "7mer_GU+", 23, 15, true, 0);
    test_sites(sites, 27, "7mer_GU+", 24, 15, true, 0);

//    test_sites(sites, 28, "MM", 0, 25, false, 0);
//    test_sites(sites, 29, "MM", 1, 25, false, 0);
//    test_sites(sites, 30, "MM", 2, 25, false, 0);
//    test_sites(sites, 31, "MM", 3, 25, false, 0);
//    test_sites(sites, 32, "MM", 4, 25, false, 0);

    test_sites(sites, 28, "7mer_MM", 16, 24, true, 4);
    test_sites(sites, 29, "8mer_MM", 17, 24, true, 4);
    test_sites(sites, 30, "8mer_MM", 18, 24, true, 4);
    test_sites(sites, 31, "8mer_MM", 19, 24, true, 4);

    test_sites(sites, 32, "7mer_MM", 20, 24, true, 5);
    test_sites(sites, 33, "8mer_MM", 21, 24, true, 5);
    test_sites(sites, 34, "8mer_MM", 22, 24, true, 5);
    test_sites(sites, 35, "8mer_MM", 23, 24, true, 5);

    test_sites(sites, 36, "7mer_MMGU", 11, 26, true, 3);
    test_sites(sites, 37, "7mer_MMGU", 12, 26, true, 3);

//    test_sites(sites, 43, "MMGU", 9, 25, false, 0);

    test_sites(sites, 38, "7mer_MMGU", 6, 24, true, 2);
    test_sites(sites, 39, "8mer_MMGU", 7, 24, true, 2);
    test_sites(sites, 40, "8mer_MMGU", 8, 24, true, 2);
    test_sites(sites, 41, "8mer_MMGU", 9, 24, true, 2);

    test_sites(sites, 42, "7mer_MMGU", 0, 24, true, 2);
    test_sites(sites, 43, "7mer_MMGU", 1, 24, true, 2);
    test_sites(sites, 44, "8mer_MMGU", 2, 24, true, 2);
    test_sites(sites, 45, "8mer_MMGU", 3, 24, true, 2);

    test_sites(sites, 46, "8mer_MMGU", 14, 24, true, 3);
    test_sites(sites, 47, "8mer_MMGU", 15, 24, true, 3);

    test_sites(sites, 48, "7mer_MMGU", 11, 24, true, 3);
    test_sites(sites, 49, "8mer_MMGU", 12, 24, true, 3);
    test_sites(sites, 50, "8mer_MMGU", 13, 24, true, 3);

//    test_sites(sites, 57, "BT", 20, 23, false, 0);
//    test_sites(sites, 58, "BT", 21, 23, false, 0);
//    test_sites(sites, 59, "BT", 22, 23, false, 0);
//    test_sites(sites, 60, "BT", 23, 23, false, 0);
//    test_sites(sites, 61, "BT", 24, 23, false, 0);

    test_sites(sites, 51, "7mer_BT", 0, 24, true, 1);
    test_sites(sites, 52, "7mer_BT", 1, 24, true, 1);
    test_sites(sites, 53, "8mer_BT", 2, 24, true, 1);
    test_sites(sites, 54, "8mer_BT", 3, 24, true, 1);
    test_sites(sites, 55, "7mer_BT", 4, 24, true, 1);
    test_sites(sites, 56, "7mer_BT", 5, 24, true, 1);

    test_sites(sites, 57, "7mer_BT", 6, 24, true, 2);
    test_sites(sites, 58, "8mer_BT", 7, 24, true, 2);
    test_sites(sites, 59, "8mer_BT", 8, 24, true, 2);
    test_sites(sites, 60, "8mer_BT", 9, 24, true, 2);

    test_sites(sites, 61, "7mer_BT", 11, 24, true, 3);
    test_sites(sites, 62, "8mer_BT", 12, 24, true, 3);
    test_sites(sites, 63, "8mer_BT", 13, 24, true, 3);
    test_sites(sites, 64, "8mer_BT", 14, 24, true, 3);
    test_sites(sites, 65, "8mer_BT", 15, 24, true, 3);

    test_sites(sites, 66, "7mer_BT", 16, 24, true, 4);
    test_sites(sites, 67, "8mer_BT", 17, 24, true, 4);
    test_sites(sites, 68, "8mer_BT", 18, 24, true, 4);
    test_sites(sites, 69, "8mer_BT", 19, 24, true, 4);

    test_sites(sites, 70, "7mer_BT", 20, 24, true, 5);
    test_sites(sites, 71, "8mer_BT", 21, 24, true, 5);
    test_sites(sites, 72, "8mer_BT", 22, 24, true, 5);
    test_sites(sites, 73, "8mer_BT", 23, 24, true, 5);
}

}
