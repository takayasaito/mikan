#ifndef MIKAN_TEST_RH2_HPP_
#define MIKAN_TEST_RH2_HPP_

#include "test_main_io.hpp"
#include "test_seed.hpp"
#include "test_site.hpp"
#include "mk_core_main.hpp"
#include "rh2_core.hpp"
#include "mk_input.hpp"

typedef TestSeed<rh2mfe::RH2Options, rh2mfe::RH2SeedSeqs> TestSeedRH2;
typedef TestSite<rh2mfe::RH2Options, rh2mfe::RH2SeedSeqs, rh2mfe::RH2SeedSites> TestSiteRH2;

#endif //MIKAN_TEST_RH2_HPP_
