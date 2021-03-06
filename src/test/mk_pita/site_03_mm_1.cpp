#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_pita.hpp"

namespace {

class Site03MM1 : public TestSitePITA {
protected:
    Site03MM1() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "ts_03_mm_1.fasta";

        resize(mSeedDef, 6);
        mSeedDef[0] = 'Y';
        mSeedDef[1] = 'Y';
        mSeedDef[2] = 'Y';
        mSeedDef[3] = "0";
        mSeedDef[4] = "1:1";
        mSeedDef[5] = "0";
    }

};

TEST_F(Site03MM1, mir124_mm7) {
    create_seed_seqs(0);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(28u, sites.get_length());

    test_sites(sites, 0, "6mer", 0, 24, true, 0);
    test_sites(sites, 1, "6mer", 1, 24, true, 0);
    test_sites(sites, 2, "8mer_MM", 2, 24, true, -1);
    test_sites(sites, 3, "8mer_MM", 3, 24, true, -1);

//    test_sites(sites, 4, "MM", 4, 24, false, 0);
//    test_sites(sites, 5, "MM", 5, 24, false, 0);
    test_sites(sites, 4, "7mer_MM", 6, 24, true, 0);
    test_sites(sites, 5, "7mer_MM", 7, 24, true, 0);
    test_sites(sites, 6, "8mer_MM", 8, 24, true, 0);
    test_sites(sites, 7, "8mer_MM", 9, 24, true, 0);

//    test_sites(sites, 10, "MM", 10, 24, false, 0);
//    test_sites(sites, 11, "MM", 11, 24, false, 0);
    test_sites(sites, 8, "7mer_MM", 12, 24, true, 1);
    test_sites(sites, 9, "7mer_MM", 13, 24, true, 1);
    test_sites(sites, 10, "8mer_MM", 14, 24, true, 1);
    test_sites(sites, 11, "8mer_MM", 15, 24, true, 1);

//    test_sites(sites, 16, "MM", 16, 24, false, 0);
//    test_sites(sites, 17, "MM", 17, 24, false, 0);
    test_sites(sites, 12, "7mer_MM", 18, 24, true, 2);
    test_sites(sites, 13, "7mer_MM", 19, 24, true, 2);
    test_sites(sites, 14, "8mer_MM", 20, 24, true, 2);
    test_sites(sites, 15, "8mer_MM", 21, 24, true, 2);

//    test_sites(sites, 22, "MM", 22, 24, false, 0);
//    test_sites(sites, 23, "MM", 23, 24, false, 0);
    test_sites(sites, 16, "7mer_MM", 24, 24, true, 3);
    test_sites(sites, 17, "7mer_MM", 25, 24, true, 3);
    test_sites(sites, 18, "8mer_MM", 26, 24, true, 3);
    test_sites(sites, 19, "8mer_MM", 27, 24, true, 3);

//    test_sites(sites, 28, "MM", 28, 24, false, 0);
//    test_sites(sites, 29, "MM", 29, 24, false, 0);
    test_sites(sites, 20, "7mer_MM", 30, 24, true, 4);
    test_sites(sites, 21, "7mer_MM", 31, 24, true, 4);
    test_sites(sites, 22, "8mer_MM", 32, 24, true, 4);
    test_sites(sites, 23, "8mer_MM", 33, 24, true, 4);

//    test_sites(sites, 34, "MM", 34, 24, false, 0);
//    test_sites(sites, 35, "MM", 35, 24, false, 0);
    test_sites(sites, 24, "7mer_MM", 36, 24, true, 5);
    test_sites(sites, 25, "7mer_MM", 37, 24, true, 5);
    test_sites(sites, 26, "8mer_MM", 38, 24, true, 5);
    test_sites(sites, 27, "8mer_MM", 39, 24, true, 5);
}

TEST_F(Site03MM1, mir124_mm8) {
    mSeedDef[4] = "0:1";
    create_seed_seqs(0);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(16u, sites.get_length());

    test_sites(sites, 0, "6mer", 0, 24, true, 0);
    test_sites(sites, 1, "6mer", 1, 24, true, 0);
    test_sites(sites, 2, "8mer_MM", 2, 24, true, -1);
    test_sites(sites, 3, "8mer_MM", 3, 24, true, -1);

//    test_sites(sites, 4, "MM", 4, 24, false, 0);
//    test_sites(sites, 5, "MM", 5, 24, false, 0);
//    test_sites(sites, 6, "MM", 6, 24, false, 0);
//    test_sites(sites, 7, "MM", 7, 24, false, 0);
    test_sites(sites, 4, "8mer_MM", 8, 24, true, 0);
    test_sites(sites, 5, "8mer_MM", 9, 24, true, 0);

//    test_sites(sites, 10, "MM", 10, 24, false, 0);
//    test_sites(sites, 11, "MM", 11, 24, false, 0);
//    test_sites(sites, 12, "MM", 12, 24, false, 0);
//    test_sites(sites, 13, "MM", 13, 24, false, 0);
    test_sites(sites, 6, "8mer_MM", 14, 24, true, 1);
    test_sites(sites, 7, "8mer_MM", 15, 24, true, 1);

//    test_sites(sites, 16, "MM", 16, 24, false, 0);
//    test_sites(sites, 17, "MM", 17, 24, false, 0);
//    test_sites(sites, 18, "MM", 18, 24, false, 0);
//    test_sites(sites, 19, "MM", 19, 24, false, 0);
    test_sites(sites, 8, "8mer_MM", 20, 24, true, 2);
    test_sites(sites, 9, "8mer_MM", 21, 24, true, 2);

//    test_sites(sites, 22, "MM", 22, 24, false, 0);
//    test_sites(sites, 23, "MM", 23, 24, false, 0);
//    test_sites(sites, 24, "MM", 24, 24, false, 0);
//    test_sites(sites, 25, "MM", 25, 24, false, 0);
    test_sites(sites, 10, "8mer_MM", 26, 24, true, 3);
    test_sites(sites, 11, "8mer_MM", 27, 24, true, 3);

//    test_sites(sites, 28, "MM", 28, 24, false, 0);
//    test_sites(sites, 29, "MM", 29, 24, false, 0);
//    test_sites(sites, 30, "MM", 30, 24, false, 0);
//    test_sites(sites, 31, "MM", 31, 24, false, 0);
    test_sites(sites, 12, "8mer_MM", 32, 24, true, 4);
    test_sites(sites, 13, "8mer_MM", 33, 24, true, 4);

//    test_sites(sites, 34, "MM", 34, 24, false, 0);
//    test_sites(sites, 35, "MM", 35, 24, false, 0);
//    test_sites(sites, 36, "MM", 36, 24, false, 0);
//    test_sites(sites, 37, "MM", 37, 24, false, 0);
    test_sites(sites, 14, "8mer_MM", 38, 24, true, 5);
    test_sites(sites, 15, "8mer_MM", 39, 24, true, 5);
}

TEST_F(Site03MM1, mir124_def) {
    mSeedDef[3] = "1";
    mSeedDef[4] = "0:1";
    mSeedDef[5] = "1";
    create_seed_seqs(0);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(16u, sites.get_length());

    test_sites(sites, 0, "6mer", 0, 24, true, 0);
    test_sites(sites, 1, "6mer", 1, 24, true, 0);
    test_sites(sites, 2, "8mer_MM", 2, 24, true, -1);
    test_sites(sites, 3, "8mer_MM", 3, 24, true, -1);

//    test_sites(sites, 4, "MM", 4, 24, false, 0);
//    test_sites(sites, 5, "MM", 5, 24, false, 0);
//    test_sites(sites, 6, "MM", 6, 24, false, 0);
//    test_sites(sites, 7, "MM", 7, 24, false, 0);
    test_sites(sites, 4, "8mer_MM", 8, 24, true, 0);
    test_sites(sites, 5, "8mer_MM", 9, 24, true, 0);

//    test_sites(sites, 10, "MM", 10, 24, false, 0);
//    test_sites(sites, 11, "MM", 11, 24, false, 0);
//    test_sites(sites, 12, "MM", 12, 24, false, 0);
//    test_sites(sites, 13, "MM", 13, 24, false, 0);
    test_sites(sites, 6, "8mer_MM", 14, 24, true, 1);
    test_sites(sites, 7, "8mer_MM", 15, 24, true, 1);

//    test_sites(sites, 16, "MM", 16, 24, false, 0);
//    test_sites(sites, 17, "MM", 17, 24, false, 0);
//    test_sites(sites, 18, "MM", 18, 24, false, 0);
//    test_sites(sites, 19, "MM", 19, 24, false, 0);
    test_sites(sites, 8, "8mer_MM", 20, 24, true, 2);
    test_sites(sites, 9, "8mer_MM", 21, 24, true, 2);

//    test_sites(sites, 22, "MM", 22, 24, false, 0);
//    test_sites(sites, 23, "MM", 23, 24, false, 0);
//    test_sites(sites, 24, "MM", 24, 24, false, 0);
//    test_sites(sites, 25, "MM", 25, 24, false, 0);
    test_sites(sites, 10, "8mer_MM", 26, 24, true, 3);
    test_sites(sites, 11, "8mer_MM", 27, 24, true, 3);

//    test_sites(sites, 28, "MM", 28, 24, false, 0);
//    test_sites(sites, 29, "MM", 29, 24, false, 0);
//    test_sites(sites, 30, "MM", 30, 24, false, 0);
//    test_sites(sites, 31, "MM", 31, 24, false, 0);
    test_sites(sites, 12, "8mer_MM", 32, 24, true, 4);
    test_sites(sites, 13, "8mer_MM", 33, 24, true, 4);

//    test_sites(sites, 34, "MM", 34, 24, false, 0);
//    test_sites(sites, 35, "MM", 35, 24, false, 0);
//    test_sites(sites, 36, "MM", 36, 24, false, 0);
//    test_sites(sites, 37, "MM", 37, 24, false, 0);
    test_sites(sites, 14, "8mer_MM", 38, 24, true, 5);
    test_sites(sites, 15, "8mer_MM", 39, 24, true, 5);
}
}
