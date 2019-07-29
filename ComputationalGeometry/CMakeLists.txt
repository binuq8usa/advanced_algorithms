cmake_minimum_required(VERSION 2.8)
project(ComputationalGeometry CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_REQUIRED_FLAGS -std=c++17)
set(CMAKE_CXX_FLAGS "-Wall -std=c++17")
#add_definitions(-G -Wall -Werror -std=c++)

find_package(Catch2 REQUIRED)

file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.h")
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

add_executable(${PROJECT_NAME}_tests "point_test.cpp" "segment_test.cpp")
target_link_libraries(${PROJECT_NAME}_tests Catch2::Catch2 ${PROJECT_NAME})
