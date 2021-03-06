#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_miranda.hpp"

namespace {

class SeedMismatch : public TestSeedMR3AS {
protected:
    SeedMismatch() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "utr3_001.fasta";

        resize(mSeedDef, 6);
        mSeedDef[0] = 'Y';
        mSeedDef[1] = 'Y';
        mSeedDef[2] = 'Y';
        mSeedDef[3] = "0";
        mSeedDef[4] = "1:1";
        mSeedDef[5] = "0";
    }
};

TEST_F(SeedMismatch, mir124_mm) {
    create_seed_seqs(0);

    EXPECT_EQ(17u, length(mSeedSeqs.mEffectiveSeeds));

    test_seed("AAGGCA", 0, "6mer", true, 0);

    test_seed("AAGGCG", 1, "MM", true, 0);
    test_seed("AAGGCC", 2, "MM", true, 0);
    test_seed("AAGGCU", 3, "MM", true, 0);

    test_seed("AAGGUA", 4, "MM", true, 1);
    test_seed("AAGGAA", 5, "MM", true, 1);
    test_seed("AAGGGA", 6, "MM", true, 1);

    test_seed("AAGUCA", 7, "MM", true, 2);
    test_seed("AAGCCA", 8, "MM", true, 2);

    test_seed("AAUGCA", 9, "MM", true, 3);
    test_seed("AACGCA", 10, "MM", true, 3);

    test_seed("AGGGCA", 11, "MM", true, 4);
    test_seed("ACGGCA", 12, "MM", true, 4);
    test_seed("AUGGCA", 13, "MM", true, 4);

    test_seed("GAGGCA", 14, "MM", true, 5);
    test_seed("CAGGCA", 15, "MM", true, 5);
    test_seed("UAGGCA", 16, "MM", true, 5);
}

TEST_F(SeedMismatch, mir1_mm) {
    create_seed_seqs(1);

    EXPECT_EQ(15u, length(mSeedSeqs.mEffectiveSeeds));

    test_seed("GGAAUG", 0, "6mer", true, 0);

    test_seed("GGAAUU", 1, "MM", true, 0);
    test_seed("GGAAUC", 2, "MM", true, 0);

    test_seed("GGAAGG", 3, "MM", true, 1);
    test_seed("GGAAAG", 4, "MM", true, 1);

    test_seed("GGAGUG", 5, "MM", true, 2);
    test_seed("GGACUG", 6, "MM", true, 2);
    test_seed("GGAUUG", 7, "MM", true, 2);

    test_seed("GGGAUG", 8, "MM", true, 3);
    test_seed("GGCAUG", 9, "MM", true, 3);
    test_seed("GGUAUG", 10, "MM", true, 3);

    test_seed("GUAAUG", 11, "MM", true, 4);
    test_seed("GCAAUG", 12, "MM", true, 4);

    test_seed("UGAAUG", 13, "MM", true, 5);
    test_seed("CGAAUG", 14, "MM", true, 5);
}
}
