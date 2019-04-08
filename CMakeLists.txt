cmake_minimum_required(VERSION 2.8)
INCLUDE(ExternalProject)

project(movie_rental)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -fsanitize=address -fno-omit-frame-pointer")

set (gtest_disable_pthreads ON)
add_subdirectory(googletest)
include_directories(
 googletest/googlemock/include
 googletest/googletest/include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTFILES "tests/*.cpp")

add_library( impl ${SOURCES} )
add_library( ${CMAKE_PROJECT_NAME}::impl ALIAS impl )

target_include_directories(impl
			   PUBLIC
				include
			   )


add_executable("${CMAKE_PROJECT_NAME}" main.cpp)
target_link_libraries("${CMAKE_PROJECT_NAME}" ${CMAKE_PROJECT_NAME}::impl)

add_executable( unit_tests
		${TESTFILES})

target_link_libraries(unit_tests
		      ${CMAKE_PROJECT_NAME}::impl
		      gmock
		      gmock_main)
