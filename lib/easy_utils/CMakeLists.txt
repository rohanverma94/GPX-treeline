add_library(easy_utils SHARED)

find_library(unwind unwind REQUIRED)
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

target_include_directories(easy_utils PRIVATE BEFORE SYSTEM ${GLOG_INCLUDE_DIR})
target_link_directories(easy_utils PRIVATE ${GLOG_LIB_DIR})

target_sources(easy_utils PRIVATE
        easy_utils.cpp
        easy_utils.h
        extra_precision_timers.h
        high_precision_timer.cpp
        high_precision_timer.h
        timer.cpp
        timer.h)
add_dependencies(easy_utils glog_external_project)

target_link_libraries(easy_utils PRIVATE glog gflags unwind)