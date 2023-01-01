# Set minimum required version
cmake_minimum_required(VERSION 3.21)
# Set the c standard
set(C_STANDARD_REQUIRED GNU90)
# Set the c compiler
set(CMAKE_C_COMPILER "gcc")
# Set the c++ compiler
#set(CMAKE_CXX_COMPILER "gcc++")

# Set project name
project(rsa_lib)

# Set the source files 
set(src_files
    main.c
    src/rsa_prg.c
)
message(STATUS source files: ${src_files})

#
add_executable(${PROJECT_NAME} ${src_files})
#
target_include_directories(${PROJECT_NAME} PUBLIC inc/)
#