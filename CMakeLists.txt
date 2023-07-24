cmake_minimum_required(VERSION 3.25)
project(treeline_test)

set(CMAKE_CXX_STANDARD 23)
set(GFLAGS_NAMESPACE google)
if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    add_compile_options(-Wall -D_FORTIFY_SOURCE=2 -fsanitize=bounds,pointer-overflow -fsanitize-undefined-trap-on-error -Wno-ignored-qualifiers
            -Wno-unused-variable -Wno-unused-function -Wextra -mavx2 -mcx16 -m64) # -fno-elide-constructors no need for now
else ()
    add_compile_options(-Wall -D_FORTIFY_SOURCE=2 -fsanitize=bounds,pointer-overflow -fsanitize-undefined-trap-on-error -Wno-ignored-qualifiers
            -Wno-unused-variable -Wno-unused-function -Wextra -march=native)
endif ()

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_library(tbb tbb)
find_library(unwind unwind REQUIRED)
configure_file(config/Config.h.in "${CMAKE_SOURCE_DIR}/config/Config.h")

add_subdirectory(third_party/treeline)

##GLOG manual build; Conflict with GFLAGS
set(GLOG_INSTALL_DIR ${CMAKE_BINARY_DIR}/_deps/glog)
set(GLOG_INCLUDE_DIR ${GLOG_INSTALL_DIR}/include)
set(GLOG_LIB_DIR ${GLOG_INSTALL_DIR}/lib)
ExternalProject_Add(glog_external_project
        GIT_REPOSITORY "https://github.com/google/glog.git"
        GIT_TAG b33e3bad4c46c8a6345525fd822af355e5ef9446
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/glog
        PREFIX ${GLOG_INSTALL_DIR}
        INSTALL_DIR ${GLOG_INSTALL_DIR}
        CMAKE_ARGS
        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_CXX_FLAGS=${EXTERNAL_PROJECT_CMAKE_CXX_FLAGS}
        -DCMAKE_INSTALL_PREFIX:PATH=${GLOG_INSTALL_DIR}
        -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
        )

include_directories(BEFORE SYSTEM ${GLOG_INCLUDE_DIR})
link_directories(${GLOG_LIB_DIR})

add_executable(treeline_test src/db_entry.cpp lib/easy_threads/easy_threads.cpp lib/easy_threads/easy_threads.h lib/easy_utils/easy_utils.cpp lib/easy_utils/easy_utils.h lib/easy_utils/extra_precision_timers.h lib/easy_utils/high_precision_timer.cpp lib/easy_utils/high_precision_timer.h lib/easy_cli/easy_cli.cpp lib/easy_cli/easy_cli.h lib/easy_utils/timer.cpp lib/easy_utils/timer.h)
add_dependencies(treeline_test glog_external_project)
target_include_directories(treeline_test PUBLIC third_party/treeline/include ${CMAKE_SOURCE_DIR}/config)
target_link_libraries(treeline_test PUBLIC tbb treeline pg_treeline glog gflags unwind)