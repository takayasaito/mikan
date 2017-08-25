#include <iostream>
#include "gtest/gtest.h"
#include "test_miranda.hpp"

namespace {

class OM001U010 : public TestIOBase {
protected:
    OM001U010() {
        IFNAME1 = (char *) "mir_001.fasta";
        IFNAME2 = (char *) "utr3_010.fasta";
        O1FNAME1 = (char *) "test_output1_site_10.txt";
        O1FNAME2 = (char *) "test_output1_mrna_10.txt";
        O2FNAME1 = (char *) "test_output2_site_10.txt";
        O2FNAME2 = (char *) "test_output2_mrna_10.txt";
        OMPATH = (char *) "mk_miranda/";
    }
};

TEST_F(OM001U010, comp_site) {
    (void) mikan::MKCoreMain<mr3as::MR3Options, mr3as::MR3Core >(argc, (const char **) argv);
    gtest_compare_two_files(o1file1, o2file1);
}

TEST_F(OM001U010, comp_mrna) {
    (void) mikan::MKCoreMain<mr3as::MR3Options, mr3as::MR3Core >(argc, (const char **) argv);
    gtest_compare_two_files(o1file2, o2file2);
}
}