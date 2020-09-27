CMAKE_MINIMUM_REQUIRED (VERSION 2.6) 

################################################################################
# Basic Configuration
################################################################################

# Name of the Project 
PROJECT(GLEW)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/CompileOptions.txt)

# Target directory
SET(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")

################################################################################
# Project Files
################################################################################

# Find all used files of certain file-types
FILE(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/glew.c")

# Add ACGL to the include path
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/include")

################################################################################
# Defines
################################################################################

INCLUDE(${CMAKE_SOURCE_DIR}/cmake/DefinesGLEW.txt)
ADD_DEFINITIONS(${GLEW_DEFINES})

################################################################################
# Final Definition
################################################################################

# Define the Project, add all required sources and dependencies to it
ADD_LIBRARY(GLEW${COMPILE_POSTFIX} STATIC ${SOURCE_FILES})

