cmake_minimum_required(VERSION 3.10)

# set the project name
project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -pedantic -Werror -ldl)

if(CMAKE_BUILD_TYPE STREQUAL "Testing")
        add_compile_options(${CMAKE_CXX_FLAGS_DEBUG} -DTEST_BUILD -DEXCLUDE_SCRIPTING)
endif()

add_definitions(-DELPP_CUSTOM_OUT=std::cerr -DELPP_THREAD_SAFE -DELPP_FEATURE_PERFORMANCE_TRACKING)

include_directories(".")


file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_executable(raytracer
                ${SOURCE_FILES}
                ./easylogging++.cc)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(raytracer ${CMAKE_DL_LIBS} Threads::Threads)

