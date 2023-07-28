enable_testing()


## Google Test integration
set(GTEST_INSTALL_DIR ${CMAKE_BINARY_DIR}/_deps/googletest)
set(GTEST_INCLUDE_DIR ${GTEST_INSTALL_DIR}/include)
set(GTEST_LIB_DIR ${GTEST_INSTALL_DIR}/lib)
ExternalProject_Add(googletest_external_project
        GIT_REPOSITORY "https://github.com/google/googletest.git"
        GIT_TAG b796f7d44681514f58a683a3a71ff17c94edb0c1
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/googletest
        PREFIX ${GTEST_INSTALL_DIR}
        INSTALL_DIR ${GTEST_INSTALL_DIR}
        CMAKE_ARGS
        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_CXX_FLAGS=${EXTERNAL_PROJECT_CMAKE_CXX_FLAGS}
        -DCMAKE_INSTALL_PREFIX:PATH=${GTEST_INSTALL_DIR}
        -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
        )

add_executable(testbench dummy.cpp)
add_dependencies(testbench googletest_external_project)

target_include_directories(testbench PRIVATE ${GTEST_INCLUDE_DIR})
target_link_directories(testbench PRIVATE ${GTEST_LIB_DIR})
target_link_libraries(
        testbench
        gtest_main
        gtest
)
target_sources(testbench PRIVATE
        dummy.cpp
        )
include(GoogleTest)
gtest_discover_tests(testbench)
