#include<string>
#include <seqan/sequence.h>
#include "gtest/gtest.h"
#include "test_mkens.hpp"

namespace {

class Site02GU2 : public TestSiteMKENS {
protected:
    Site02GU2() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "ts_02_gu_2.fasta";
    }

};

TEST_F(Site02GU2, mir1) {
    read_and_set_seqs();
    TIdx index(mrna_seqs);
    TFin finder(index);
    mkens::MKECore mkCore(mOpts, mirna_ids, mirna_seqs, mrna_ids, mrna_seqs, index, finder);
    mkCore.find_seed_sites(1);
    TSit &sites = mkCore.get_seed_sites();

    EXPECT_EQ(83u, sites.get_length());

    test_sites(sites, 0, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 0, 18, true, 0);
    test_sites(sites, 1, "mr:7mer_BT,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 0, 29, true, 0);
    test_sites(sites, 2, "mr:7mer_GUM,pt:6mer,rh:7mer_GUM,tm:6mer,ts:NA,sv:6mer,", 0, 30, true, 0);
    test_sites(sites, 3, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 1, 18, true, 0);
    test_sites(sites, 4, "mr:7mer_BT,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 1, 29, true, 0);
    test_sites(sites, 5, "mr:7mer_GUM,pt:6mer,rh:7mer_GUM,tm:7mer-A1,ts:7mer-A1,sv:7mer-A1,", 1, 30, true, 0);
    test_sites(sites, 6, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 2, 18, true, 0);
    test_sites(sites, 7, "mr:8mer_GUM,pt:8mer_GUM,rh:7mer_GUM,tm:6mer,ts:NA,sv:6mer,", 2, 30, true, 0);
    test_sites(sites, 8, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 3, 18, true, 0);
    test_sites(sites, 9, "mr:8mer_GUM,pt:8mer_GUM,rh:7mer_GUM,tm:7mer-A1,ts:7mer-A1,sv:7mer-A1,", 3, 30, true, 0);
    test_sites(sites, 10, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 4, 18, true, 0);
    test_sites(sites, 11, "mr:7mer_GUT,pt:7mer_GUT,rh:7mer_GUT,tm:7mer-m8,ts:NA,sv:NA,", 4, 30, true, 0);
    test_sites(sites, 12, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 5, 18, true, 0);
    test_sites(sites, 13, "mr:7mer_GUT,pt:7mer_GUT,rh:7mer_GUT,tm:8mer,ts:NA,sv:GUM,", 5, 30, true, 0);
    test_sites(sites, 14, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 6, 18, true, 0);
    test_sites(sites, 15, "mr:8mer_GUT,pt:8mer_GUT,rh:7mer_GUT,tm:7mer-m8,ts:NA,sv:NA,", 6, 30, true, 0);
    test_sites(sites, 16, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 7, 18, true, 0);
    test_sites(sites, 17, "mr:8mer_GUT,pt:8mer_GUT,rh:7mer_GUT,tm:8mer,ts:NA,sv:GUM,", 7, 30, true, 0);
    test_sites(sites, 18, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 8, 18, true, 0);
    test_sites(sites, 19, "mr:7mer_BT,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 8, 29, true, 0);
    test_sites(sites, 20, "mr:7mer_MMGU,pt:NA,rh:NA,tm:6mer,ts:NA,sv:NA,", 8, 30, true, 0);
    test_sites(sites, 21, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 9, 18, true, 0);
    test_sites(sites, 22, "mr:7mer_GU+,pt:NA,rh:7mer_GUM,tm:6mer,ts:NA,sv:NA,", 9, 30, true, 0);
    test_sites(sites, 23, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 10, 18, true, 0);
    test_sites(sites, 24, "mr:7mer_GU+,pt:NA,rh:7mer_GUM,tm:7mer-A1,ts:NA,sv:NA,", 10, 30, true, 0);
    test_sites(sites, 25, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 11, 18, true, 0);
    test_sites(sites, 26, "mr:8mer_GU+,pt:NA,rh:7mer_GUM,tm:6mer,ts:NA,sv:NA,", 11, 30, true, 0);
    test_sites(sites, 27, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 12, 18, true, 0);
    test_sites(sites, 28, "mr:8mer_GU+,pt:NA,rh:7mer_GUM,tm:7mer-A1,ts:NA,sv:NA,", 12, 30, true, 0);
    test_sites(sites, 29, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 13, 18, true, 0);
    test_sites(sites, 30, "mr:7mer_GUM,pt:7mer_GUM,rh:7mer_GUM,tm:7mer-m8,ts:NA,sv:NA,", 13, 30, true, 0);
    test_sites(sites, 31, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 14, 18, true, 0);
    test_sites(sites, 32, "mr:7mer_GUM,pt:7mer_GUM,rh:7mer_GUM,tm:8mer,ts:NA,sv:GUT,", 14, 30, true, 0);
    test_sites(sites, 33, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 15, 18, true, 0);
    test_sites(sites, 34, "mr:8mer_GUM,pt:8mer_GUM,rh:7mer_GUM,tm:7mer-m8,ts:NA,sv:NA,", 15, 30, true, 0);
    test_sites(sites, 35, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 16, 18, true, 0);
    test_sites(sites, 36, "mr:8mer_GUM,pt:8mer_GUM,rh:7mer_GUM,tm:8mer,ts:NA,sv:GUT,", 16, 30, true, 0);
    test_sites(sites, 37, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 17, 18, true, 0);
    test_sites(sites, 38, "mr:7mer_MMGU,pt:NA,rh:NA,tm:6mer,ts:NA,sv:NA,", 17, 30, true, 0);
    test_sites(sites, 39, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 18, 18, true, 0);
    test_sites(sites, 40, "mr:7mer_GU+,pt:NA,rh:7mer_GUM,tm:6mer,ts:NA,sv:NA,", 18, 30, true, 0);
    test_sites(sites, 41, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 19, 18, true, 0);
    test_sites(sites, 42, "mr:7mer_GU+,pt:NA,rh:7mer_GUM,tm:7mer-A1,ts:NA,sv:NA,", 19, 30, true, 0);
    test_sites(sites, 43, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 20, 18, true, 0);
    test_sites(sites, 44, "mr:8mer_GU+,pt:NA,rh:7mer_GUM,tm:6mer,ts:NA,sv:NA,", 20, 30, true, 0);
    test_sites(sites, 45, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 21, 18, true, 0);
    test_sites(sites, 46, "mr:8mer_GU+,pt:NA,rh:7mer_GUM,tm:7mer-A1,ts:NA,sv:NA,", 21, 30, true, 0);
    test_sites(sites, 47, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 22, 18, true, 0);
    test_sites(sites, 48, "mr:7mer_GUT,pt:7mer_GUT,rh:7mer_GUT,tm:7mer-m8,ts:NA,sv:BT,", 22, 30, true, 0);
    test_sites(sites, 49, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 23, 18, true, 0);
    test_sites(sites, 50, "mr:7mer_GUT,pt:7mer_GUT,rh:7mer_GUT,tm:8mer,ts:NA,sv:GUM,", 23, 30, true, 0);
    test_sites(sites, 51, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 24, 18, true, 0);
    test_sites(sites, 52, "mr:8mer_GUT,pt:8mer_GUT,rh:7mer_GUT,tm:7mer-m8,ts:NA,sv:BT,", 24, 30, true, 0);
    test_sites(sites, 53, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 25, 18, true, 0);
    test_sites(sites, 54, "mr:8mer_GUT,pt:8mer_GUT,rh:7mer_GUT,tm:8mer,ts:NA,sv:GUM,", 25, 30, true, 0);
    test_sites(sites, 55, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 26, 18, true, 0);
    test_sites(sites, 56, "mr:7mer_MMGU,pt:NA,rh:NA,tm:6mer,ts:NA,sv:NA,", 26, 30, true, 0);
    test_sites(sites, 57, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 27, 18, true, 0);
    test_sites(sites, 58, "mr:7mer_GU+,pt:NA,rh:7mer_GUM,tm:6mer,ts:NA,sv:NA,", 27, 30, true, 0);
    test_sites(sites, 59, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 28, 18, true, 0);
    test_sites(sites, 60, "mr:7mer_GU+,pt:NA,rh:7mer_GUM,tm:7mer-A1,ts:NA,sv:NA,", 28, 30, true, 0);
    test_sites(sites, 61, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 29, 18, true, 0);
    test_sites(sites, 62, "mr:8mer_GU+,pt:NA,rh:7mer_GUM,tm:6mer,ts:NA,sv:NA,", 29, 30, true, 0);
    test_sites(sites, 63, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 30, 18, true, 0);
    test_sites(sites, 64, "mr:8mer_GU+,pt:NA,rh:7mer_GUM,tm:7mer-A1,ts:NA,sv:NA,", 30, 30, true, 0);
    test_sites(sites, 65, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 31, 18, true, 0);
    test_sites(sites, 66, "mr:7mer_GUT,pt:7mer_GUT,rh:7mer_GUT,tm:7mer-m8,ts:NA,sv:BT,", 31, 30, true, 0);
    test_sites(sites, 67, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 32, 18, true, 0);
    test_sites(sites, 68, "mr:7mer_GUT,pt:7mer_GUT,rh:7mer_GUT,tm:8mer,ts:NA,sv:GUM,", 32, 30, true, 0);
    test_sites(sites, 69, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 33, 18, true, 0);
    test_sites(sites, 70, "mr:8mer_GUT,pt:8mer_GUT,rh:7mer_GUT,tm:7mer-m8,ts:NA,sv:BT,", 33, 30, true, 0);
    test_sites(sites, 71, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 34, 18, true, 0);
    test_sites(sites, 72, "mr:8mer_GUT,pt:8mer_GUT,rh:7mer_GUT,tm:8mer,ts:NA,sv:GUM,", 34, 30, true, 0);
    test_sites(sites, 73, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 35, 18, true, 0);
    test_sites(sites, 74, "mr:7mer_MMGU,pt:NA,rh:NA,tm:6mer,ts:NA,sv:NA,", 35, 30, true, 0);
    test_sites(sites, 75, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 36, 18, true, 0);
    test_sites(sites, 76, "mr:7mer_GU+,pt:NA,rh:7mer_GUM,tm:6mer,ts:NA,sv:NA,", 36, 30, true, 0);
    test_sites(sites, 77, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 37, 18, true, 0);
    test_sites(sites, 78, "mr:7mer_GU+,pt:NA,rh:7mer_GUM,tm:7mer-A1,ts:NA,sv:NA,", 37, 30, true, 0);
    test_sites(sites, 79, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 38, 18, true, 0);
    test_sites(sites, 80, "mr:8mer_GU+,pt:NA,rh:7mer_GUM,tm:6mer,ts:NA,sv:NA,", 38, 30, true, 0);
    test_sites(sites, 81, "mr:7mer_MMGU,pt:NA,rh:NA,tm:NA,ts:NA,sv:NA,", 39, 18, true, 0);
    test_sites(sites, 82, "mr:8mer_GU+,pt:NA,rh:7mer_GUM,tm:7mer-A1,ts:NA,sv:NA,", 39, 30, true, 0);

}
}
