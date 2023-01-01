#########################################################
######### CMAKE BASIC CONFIGURATIONS ####################
#########################################################
# Set minimum required version
cmake_minimum_required(VERSION 3.10)
# Set the c standard
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
message(STATUS C_STANDARD: ${CMAKE_C_STANDARD})
# Set the c compiler
set(CMAKE_C_COMPILER "gcc")
# Set the c++ compiler
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS CXX_STANDARD: ${CMAKE_CXX_STANDARD})
#########################################################
######### CMAKE PROJECT CONFIGURATIONS ##################
#########################################################
# Set project name
project(rsa_lib VERSION 0.0)
# Set the source files 
file(GLOB_RECURSE src_files src/*.c)
message(STATUS source files: ${src_files})
#
add_executable(${PROJECT_NAME} main.c ${src_files})
#
target_include_directories(${PROJECT_NAME} PUBLIC 
                        ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#