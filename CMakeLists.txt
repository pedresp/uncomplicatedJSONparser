cmake_minimum_required(VERSION 3.10)
project(UJP VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(ujp_lib)

add_executable(main main.cpp)
add_executable(failed_parser examples/failed_parser.cpp)

target_link_libraries(main PRIVATE ujp_lib)
target_link_libraries(failed_parser PRIVATE ujp_lib)