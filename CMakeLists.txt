cmake_minimum_required(VERSION 3.8)

set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 9)
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(ip_filter VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(ip_filter main.cpp)

add_library(filter ip_filter.h ip_filter.cpp)

add_executable(ip_test just_test.cpp ip_filter.h ip_filter.cpp)

set(target "ip_test" "filter" "ip_test")

function(set_warning_flags target)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
                target_compile_options(${target} PRIVATE "-Wall" "-Wextra" "-pedantic-errors")
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
                target_compile_options(${target} PRIVATE "/W4")
        endif()
endfunction()


set_target_properties(ip_test PROPERTIES
 COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
 INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
 LINK_LIBRARIES ${Boost_LIBRARIES}
)

target_link_libraries(ip_filter
    filter
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT dontevenwriteme@example.com)

include(CPack)
enable_testing ()
add_test (ip_test ip_test)
