#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_tssvm.hpp"

namespace {

class Site05BT1 : public TestSiteTSSVM {
protected:
    Site05BT1() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "ts_05_bt_1.fasta";
    }

};

TEST_F(Site05BT1, mir124_bt) {
    create_seed_seqs(0);
    TIdx index(mrna_seqs);
    TFin finder(index);
    TSit sites(index, finder, mrna_seqs);
    find_seed_sites(sites);
    
    EXPECT_EQ(22u, sites.get_length());

    test_sites(sites, 0, "BT", 1, 24, true, 6);
    test_sites(sites, 1, "BT", 3, 24, true, 6);

    test_sites(sites, 2, "BT", 8, 24, true, 5);
    test_sites(sites, 3, "BT", 9, 24, true, 5);
    test_sites(sites, 4, "BT", 10, 24, true, 5);

    test_sites(sites, 5, "BT", 13, 24, true, 4);
    test_sites(sites, 6, "BT", 9, 24, true, 4);
    test_sites(sites, 7, "BT", 14, 24, true, 4);
    test_sites(sites, 8, "BT", 15, 24, true, 4);

    test_sites(sites, 9, "BT", 18, 24, true, 3);
    test_sites(sites, 10, "BT", 9, 24, true, 3);
    test_sites(sites, 11, "BT", 19, 24, true, 3);

    test_sites(sites, 12, "BT", 22, 24, true, 2);
    test_sites(sites, 13, "BT", 23, 24, true, 2);
    test_sites(sites, 14, "BT", 24, 24, true, 2);

    test_sites(sites, 15, "BM", 10, 25, true, 5);
    test_sites(sites, 16, "BM", 20, 23, true, 2);
    test_sites(sites, 17, "BM", 21, 23, true, 2);
    test_sites(sites, 18, "BM", 22, 23, true, 2);
    test_sites(sites, 19, "BM", 20, 23, true, 1);
    test_sites(sites, 20, "BM", 21, 23, true, 1);
    test_sites(sites, 21, "BM", 22, 23, true, 1);
}

}
