add_library(ujp_lib ujp_json.cpp ujp_json.hpp ujp_scanner.cpp ujp_scanner.hpp)

target_include_directories(ujp_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})