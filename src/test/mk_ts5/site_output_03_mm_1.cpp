#include <iostream>
#include "gtest/gtest.h"
#include "test_ts5.hpp"

namespace {

class SiteOut03MM1 : public TestIOBase {
protected:
    SiteOut03MM1() {
        IFNAME1 = (char *) "mir_003.fasta";
        IFNAME2 = (char *) "ts_03_mm_1.fasta";
        O1FNAME1 = (char *) "so03_mm_1_site_orig.txt";
        O1FNAME2 = (char *) "so03_mm_1_mrna_orig.txt";
        O2FNAME1 = (char *) "so03_mm_1_site_mk.txt";
        O2FNAME2 = (char *) "so03_mm_1_mrna_mk.txt";
        OMPATH = (char *) "mk_ts5/";
    }
};

TEST_F(SiteOut03MM1, comp_orig_mk) {
    (void) mikan::MKCoreMain<ts5cs::TS5Options, ts5cs::TS5Core >(argc, (const char **) argv);
    gtest_compare_two_files(o1file1, o2file1);
    gtest_compare_two_files(o1file2, o2file2);
}
}