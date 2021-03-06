#ifndef MIKAN_TEST_TSSVM_HPP_
#define MIKAN_TEST_TSSVM_HPP_

#include "test_main_io.hpp"
#include "test_seed.hpp"
#include "test_site.hpp"
#include "mk_core_main.hpp"
#include "tssvm_core.hpp"
#include "mk_input.hpp"

typedef TestSeed<tssvm::TSSVMOptions, tssvm::TSSVMSeedSeqs> TestSeedTSSVM;
typedef TestSite<tssvm::TSSVMOptions, tssvm::TSSVMSeedSeqs, tssvm::TSSVMSeedSites> TestSiteTSSVM;

#endif //MIKAN_TEST_TSSVM_HPP_
