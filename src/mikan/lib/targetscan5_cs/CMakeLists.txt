cmake_minimum_required(VERSION 2.8.2)

# Add sub directory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lm)

set(TS5_SOURCE
        ${TS5_LM_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/ts5_core.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ts5_option.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ts5_seed_site.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ts5_site_score.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ts5_align.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ts5_rna_score.cpp
        PARENT_SCOPE
        )
set(TS5_HEADERS
        ${TS5_LM_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PARENT_SCOPE
        )

