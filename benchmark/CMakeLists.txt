cmake_minimum_required(VERSION 2.8.12)
     
project(trtree_benchmark)
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++14" CACHE STRING "compile flags" FORCE)
 
file(GLOB SRC_FILES ../rtree/tree.cpp ../rtree/split.cpp ../rtree/geometry.cpp)
file(GLOB HDR_FILES "../rtree/*.hpp")
file(GLOB SRC_TEST_FILES "tests/*.cpp")

add_executable(trtree_benchmark ${SRC_FILES} ${HDR_FILES} ${SRC_TEST_FILES})
