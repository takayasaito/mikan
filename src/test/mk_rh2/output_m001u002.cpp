#include <iostream>
#include "gtest/gtest.h"
#include "test_rh2.hpp"

namespace {

class OM001U002 : public TestIORH2 {
protected:
    OM001U002() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "utr3_002.fasta";
        O1FNAME1 = (char *) "test_output1_site_2.txt";
        O1FNAME2 = (char *) "test_output1_mrna_2.txt";
        O2FNAME1 = (char *) "test_output2_site_2.txt";
        O2FNAME2 = (char *) "test_output2_mrna_2.txt";
        OMPATH = (char *) "mk_rh2/";
    }
};

TEST_F(OM001U002, comp_site) {
    (void) rh2mfe::RH2CoreMain(argc, (const char **) argv);
    gtest_compare_two_files(o1file1, o2file1);
}

TEST_F(OM001U002, comp_mrna) {
    (void) rh2mfe::RH2CoreMain(argc, (const char **) argv);
    gtest_compare_two_files(o1file2, o2file2);
}
}