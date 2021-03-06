project(test_mk_mkens)

cmake_minimum_required(VERSION 2.8.2)

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Search dependencies
set(SEQAN_FIND_DEPENDENCIES NONE)
find_package(SeqAn REQUIRED)

# ----------------------------------------------------------------------------
# Build Setup
# ----------------------------------------------------------------------------

add_subdirectory(${CMAKE_SOURCE_DIR}/mikan/lib/mikan_ens mkens)
add_subdirectory(${CMAKE_SOURCE_DIR}/mikan/lib/miranda3 mr3as)
add_subdirectory(${CMAKE_SOURCE_DIR}/mikan/lib/pita_ddg pita)
add_subdirectory(${CMAKE_SOURCE_DIR}/mikan/lib/rnahybrid2_mfe rh2)
add_subdirectory(${CMAKE_SOURCE_DIR}/mikan/lib/targetminer1 tm1)
add_subdirectory(${CMAKE_SOURCE_DIR}/mikan/lib/targetscan5_cs ts5)
add_subdirectory(${CMAKE_SOURCE_DIR}/mikan/lib/two_step_svm tssvm)
add_subdirectory(${CMAKE_SOURCE_DIR}/mikan/lib/vienna_rna vrna)
add_subdirectory(${CMAKE_SOURCE_DIR}/mikan/lib/mikan_base mkbase)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lib/mikan mikantest)

# Add include directories
include_directories(${SEQAN_INCLUDE_DIRS}
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        ${MKE_HEADERS}
        ${MR3_HEADERS}
        ${PITA_HEADERS}
        ${RH2_HEADERS}
        ${TM1_HEADERS}
        ${TS5_HEADERS}
        ${TSSVM_HEADERS}
        ${VR16_HEADERS}
        ${MIKAN_HEADERS}
        ${MKTEST_HEADERS})

# Add definitions set by find_package (SeqAn)
add_definitions(${SEQAN_DEFINITIONS})
if (MSVC)
    add_definitions(/D TEST_DATA_PATH=${CMAKE_CURRENT_LIST_DIR}/../data/)
else ()
    add_definitions(-DTEST_DATA_PATH=${CMAKE_CURRENT_LIST_DIR}/../data/)
endif ()

# Add executable applications
add_executable(gtest_mk_mkens
        site_01_nmer_1.cpp site_01_nmer_2.cpp site_02_gu_1.cpp site_02_gu_2.cpp site_03_mm_1.cpp site_03_mm_2.cpp
        site_04_mmgu_1.cpp site_04_mmgu_2.cpp site_05_bt_1.cpp site_05_bt_2.cpp site_06_bm_1.cpp site_06_bm_2.cpp
        site_output_01_nmer_1.cpp site_output_01_nmer_2.cpp site_output_02_gu_1.cpp site_output_02_gu_2.cpp
        site_output_03_mm_1.cpp site_output_03_mm_2.cpp site_output_04_mmgu_1.cpp site_output_04_mmgu_2.cpp
        site_output_05_bt_1.cpp site_output_05_bt_2.cpp site_output_06_bm_1.cpp site_output_06_bm_2.cpp)

add_executable(gtest_mk_mkens_long output_m001u001.cpp output_m001u002.cpp output_m001u003.cpp output_m001u004.cpp
        output_m001u005.cpp output_m001u006.cpp output_m001u007.cpp output_m001u008.cpp output_m001u009.cpp
        output_m001u010.cpp output_m001u011.cpp)

# Add libraries
if (NOT TARGET mikantest)
    add_library(mikantest ${MKTEST_SOURCE})
endif ()

# Add dependencies found by find_package (SeqAn)
target_link_libraries(gtest_mk_mkens gtest gtest_main)
target_link_libraries(gtest_mk_mkens ${SEQAN_LIBRARIES} mkens mr3as pita rh2 tm1 ts5 tssvm vrna mkbase mikantest)
target_link_libraries(gtest_mk_mkens_long gtest gtest_main)
target_link_libraries(gtest_mk_mkens_long ${SEQAN_LIBRARIES} mkens mr3as pita rh2 tm1 ts5 tssvm vrna mkbase mikantest)

# Add CXX flags found by find_package (SeqAn)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SEQAN_CXX_FLAGS}")

# Define helper functions and macros used by Google Test.
include(${CMAKE_CURRENT_SOURCE_DIR}/../lib/googletest/cmake/internal_utils.cmake)
config_compiler_and_linker()  # Defined in internal_utils.cmake.

# Add test
add_test(NAME gtest_mk_mkens COMMAND gtest_mk_mkens)
add_test(NAME gtest_mk_mkens_long COMMAND gtest_mk_mkens_long)
