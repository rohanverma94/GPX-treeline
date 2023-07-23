cmake_minimum_required(VERSION 3.25)
project(treeline_test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_library(tbb tbb)


configure_file(config/Config.h.in ${CMAKE_SOURCE_DIR}/config/Config.h)


add_subdirectory(third_party/treeline)
include_directories(config)
add_executable(treeline_test src/main.cpp)
target_include_directories(treeline_test PUBLIC third_party/treeline/include)
target_link_libraries(treeline_test PUBLIC tbb treeline pg_treeline)