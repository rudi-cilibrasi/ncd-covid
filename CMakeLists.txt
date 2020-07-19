cmake_minimum_required(VERSION 3.16)

project(covidcompression)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  message(STATUS "Build type not specified: Use Debug by default")
endif(NOT CMAKE_BUILD_TYPE)

include_directories(src)
set(CMAKE_CXX_STANDARD 17)

set(COMMON_LIB_SRCS
src/crc64.c
src/basicCompressor.cpp
src/basicCompressor.hpp
src/cachingCompressor.cpp
src/cachingCompressor.hpp
src/datasource.cpp
src/datasource.hpp
src/displayName.cpp
src/displayName.hpp
src/distMatrixWriter.cpp
src/distMatrixWriter.hpp
src/entryAndNCD.cpp
src/entryAndNCD.hpp
src/envutil.cpp
src/envutil.hpp
src/fsutil.cpp
src/fsutil.hpp
src/humanMito.cpp
src/humanMito.hpp
src/nameAndCRC.cpp
src/nameAndCRC.hpp
src/ncdHelper.cpp
src/ncdHelper.hpp
src/ncdSortedEntryList.cpp
src/ncdSortedEntryList.hpp
src/rocksHelper.cpp
src/rocksHelper.hpp
src/selectedSequence.cpp
src/selectedSequence.hpp
src/seqNameHelper.cpp
src/seqNameHelper.hpp
src/sequenceCompressor.cpp
src/sequenceCompressor.hpp
src/sequenceReader.cpp
src/sequenceReader.hpp
src/taggedSequenceCombination.cpp
src/taggedSequenceCombination.hpp
src/treeMaker.cpp
src/treeMaker.hpp
src/textutil.cpp
)

add_library(common ${COMMON_LIB_SRCS})

set(TEST_MAIN_SRCS src/main.cpp)
add_executable(test_main ${TEST_MAIN_SRCS})

set(IMPORTER_MAIN_SRCS src/importer-main.cpp)
add_executable(importer ${IMPORTER_MAIN_SRCS})

set(CLEANER_MAIN_SRCS src/cleaner-main.cpp)
add_executable(cleaner ${CLEANER_MAIN_SRCS})

set(SORT_EVERYTHING_SRCS src/sort-everything-main.cpp)
add_executable(sort-everything ${SORT_EVERYTHING_SRCS})

set(TREE_FIRST_SRCS src/tree-first-main.cpp)
add_executable(tree-first ${TREE_FIRST_SRCS})

set(TREE_SECOND_SRCS src/tree-second-main.cpp)
add_executable(tree-second ${TREE_SECOND_SRCS})

target_link_libraries(test_main common)
target_link_libraries(importer common rocksdb fastahack)
target_link_libraries(cleaner common rocksdb)
target_link_libraries(sort-everything common rocksdb)
target_link_libraries(tree-first common rocksdb)
target_link_libraries(tree-second common rocksdb)
