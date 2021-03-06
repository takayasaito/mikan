#include <iostream>
#include "gtest/gtest.h"
#include "test_tssvm.hpp"

namespace {

class SiteOut06BM2 : public TestIOBase {
protected:
    SiteOut06BM2() {
        IFNAME1 = (char *) "mir_004.fasta";
        IFNAME2 = (char *) "ts_06_bm_2.fasta";
        O1FNAME1 = (char *) "so06_bm_2_site_orig.txt";
        O1FNAME2 = (char *) "so06_bm_2_mrna_orig.txt";
        O2FNAME1 = (char *) "so06_bm_2_site_mk.txt";
        O2FNAME2 = (char *) "so06_bm_2_mrna_mk.txt";
        OMPATH = (char *) "mk_tssvm/";
    }
};

TEST_F(SiteOut06BM2, comp_orig_mk) {
    (void) mikan::MKCoreMain<tssvm::TSSVMOptions, tssvm::TSSVMCore >(argc, (const char **) argv);
    gtest_compare_two_files2(o1file1, o2file1, 5, 100, 1);
    gtest_compare_two_files2(o1file2, o2file2, 2, 100, 1);
}
}