#include <iostream>
#include "gtest/gtest.h"
#include "test_ts5.hpp"

namespace {

    class SiteOut04MMGU2 : public TestIOTS5
    {
    protected:
        SiteOut04MMGU2() {
            IFNAME1 = (char *)"mir_004.fasta";
            IFNAME2 = (char *)"ts_04_mmgu_2.fasta";
            O1FNAME1 = (char *)"so04_mmgu_2_site_orig.txt";
            O1FNAME2 = (char *)"so04_mmgu_2_mrna_orig.txt";
            O2FNAME1 = (char *)"so04_mmgu_2_site_mk.txt";
            O2FNAME2 = (char *)"so04_mmgu_2_mrna_mk.txt";
            OMPATH = (char *)"mk_ts5/";
        }
    };

    TEST_F(SiteOut04MMGU2, comp_orig_mk) {
        (void)ts5cs::TS5CoreMain(argc, (const char **)argv);
        gtest_compare_two_files(o1file1, o2file1);
        gtest_compare_two_files(o1file2, o2file2);
    }
}