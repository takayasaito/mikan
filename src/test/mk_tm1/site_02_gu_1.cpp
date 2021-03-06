#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_tm1.hpp"

namespace {

class Site02GU1 : public TestSiteTM1 {
protected:
    Site02GU1() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "ts_02_gu_1.fasta";
    }

};

TEST_F(Site02GU1, mir124_gu) {
    create_seed_seqs(0);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);
    
    EXPECT_EQ(11u, sites.get_length());

    test_sites(sites, 0, "7mer-m8", 0, 24, true, 0);

    test_sites(sites, 1, "6mer", 1, 24, true, 0);
    test_sites(sites, 2, "7mer-m8", 2, 24, true, 0);
    test_sites(sites, 3, "8mer", 3, 24, true, 0);
    test_sites(sites, 4, "7mer-m8", 4, 24, true, 0);
    test_sites(sites, 5, "8mer", 5, 24, true, 0);

    test_sites(sites, 6, "6mer", 6, 24, true, 0);
    test_sites(sites, 7, "7mer-m8", 7, 24, true, 0);
    test_sites(sites, 8, "8mer", 8, 24, true, 0);
    test_sites(sites, 9, "7mer-m8", 9, 24, true, 0);
    test_sites(sites, 10, "8mer", 10, 24, true, 0);
}
}
