cmake_minimum_required(VERSION 3.10)
project(lanetrotro)

# Add cJSON
add_subdirectory(external/cjson)

# Add the executable for your project
add_executable(lanetrotro src/lanetrotro.c src/lanetrotro.h)

# Link the cJSON library
target_link_libraries(lanetrotro cjson)
