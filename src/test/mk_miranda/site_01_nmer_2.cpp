#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_miranda.hpp"

namespace {

class Site01Nmer2 : public TestSiteMR3AS {
protected:
    Site01Nmer2() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "ts_01_nmer_2.fasta";

        resize(mSeedDef, 6);
        mSeedDef[0] = 'Y';
        mSeedDef[1] = 'Y';
        mSeedDef[2] = 'Y';
        mSeedDef[3] = "0";
        mSeedDef[4] = "0:0";
        mSeedDef[5] = "0";
    }

};

TEST_F(Site01Nmer2, mir1_8mer) {
    create_seed_seqs(1);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(5u, sites.get_length());

    test_sites(sites, 0, "6mer", 0, 25, true, 0);
    test_sites(sites, 1, "6mer", 1, 25, true, 0);
    test_sites(sites, 2, "7mer", 2, 25, true, 0);
    test_sites(sites, 3, "7mer", 3, 25, true, 0);
    test_sites(sites, 4, "8mer", 4, 25, true, 0);
}

TEST_F(Site01Nmer2, mir1_7mer) {
    mSeedDef[2] = 'N';
    create_seed_seqs(1);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(5u, sites.get_length());

    test_sites(sites, 0, "6mer", 0, 25, true, 0);
    test_sites(sites, 1, "6mer", 1, 25, true, 0);
    test_sites(sites, 2, "7mer", 2, 25, true, 0);
    test_sites(sites, 3, "7mer", 3, 25, true, 0);
    test_sites(sites, 4, "7mer", 4, 25, true, 0);
}

TEST_F(Site01Nmer2, mir1_6mer) {
    mSeedDef[1] = 'N';
    mSeedDef[2] = 'N';
    create_seed_seqs(1);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(5u, sites.get_length());

    test_sites(sites, 0, "6mer", 0, 25, true, 0);
    test_sites(sites, 1, "6mer", 1, 25, true, 0);
    test_sites(sites, 2, "6mer", 2, 25, true, 0);
    test_sites(sites, 3, "6mer", 3, 25, true, 0);
    test_sites(sites, 4, "6mer", 4, 25, true, 0);
}

TEST_F(Site01Nmer2, mir1_def) {
    mSeedDef[3] = "+";
    mSeedDef[4] = "1:1";
    mSeedDef[5] = "1";
    create_seed_seqs(1);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);

    EXPECT_EQ(14u, sites.get_length());

    test_sites(sites, 0, "7mer_MM", 0, 25, true, -1);
    test_sites(sites, 1, "7mer_MM", 1, 25, true, -1);
    test_sites(sites, 2, "7mer", 2, 25, true, 0);
    test_sites(sites, 3, "7mer", 3, 25, true, 0);
    test_sites(sites, 4, "8mer", 4, 25, true, 0);
    test_sites(sites, 5, "7mer_MMGU", 0, 13, true, 3);
    test_sites(sites, 6, "7mer_MMGU", 1, 13, true, 3);
    test_sites(sites, 7, "7mer_MMGU", 2, 13, true, 3);
    test_sites(sites, 8, "7mer_MMGU", 3, 13, true, 3);
    test_sites(sites, 9, "7mer_MMGU", 4, 13, true, 3);
    test_sites(sites, 10, "7mer_BT", 2, 24, true, 0);
    test_sites(sites, 11, "7mer_BT", 3, 24, true, 0);
//    test_sites(sites, 12, "BT", 4, 24, false, 0);
    test_sites(sites, 12, "7mer_BT", 0, 24, true, 0);
    test_sites(sites, 13, "7mer_BT", 1, 24, true, 0);
}

}
