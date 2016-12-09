#ifndef MIKAN_TEST_TSSVM_HPP_
#define MIKAN_TEST_TSSVM_HPP_

#include "test_main_io.hpp"
#include "test_seed.hpp"
#include "test_site.hpp"
#include "tssvm_core.hpp"

typedef TestIOBase<tssvm::TSSVMCoreInput<tssvm::TRNATYPE>, tssvm::TSSVMOptions> TestIOTSSVM;
typedef TestSeed<tssvm::TSSVMSeedSeqs<tssvm::TRNATYPE>, TestIOTSSVM> TestSeedTSSVM;
typedef TestSite<tssvm::TSSVMSeedSites<tssvm::TRNATYPE>, TestIOTSSVM> TestSiteTSSVM;

#endif //MIKAN_TEST_TSSVM_HPP_
