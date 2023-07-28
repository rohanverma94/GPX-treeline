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
configure_file(config/Config.h.in "${CMAKE_SOURCE_DIR}/config/Config.h")

add_subdirectory(third_party/treeline)

##Add libs
add_subdirectory(lib)

##Add google test
add_subdirectory(test)

add_executable(treeline_test src/db_entry.cpp)

target_include_directories(treeline_test PUBLIC third_party/treeline/include ${CMAKE_SOURCE_DIR}/config)
target_link_libraries(treeline_test PUBLIC tbb treeline pg_treeline)