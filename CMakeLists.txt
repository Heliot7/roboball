CMAKE_MINIMUM_REQUIRED (VERSION 2.6) 

################################################################################
# Basic Configuration
################################################################################

# Name of the Project 
PROJECT(Robo-ball)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/CompileOptions.txt)

# Where to find the cmake finders?
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Setup ACGL for this project
SET(ACGL_OPENGL_SUPPORT CORE_30)
SET(ACGL_ERROR_LEVEL EC1)
SET(ACGL_COMPILE_WITH_QT Yes)

# Target directory
SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Specify dependencies
SET(USE_LOCAL_GLM TRUE)
SET(USE_LOCAL_GLEW TRUE)
SET(USE_LOCAL_ACGL TRUE)
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/GlobalAndLocalExternACGL.txt)

################################################################################
# Project Files
################################################################################

# Find all used files of certain file-types
FILE(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")
FILE(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh")
FILE(GLOB_RECURSE SHADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/bin/Shader/*.*")
FILE(GLOB_RECURSE MOC_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/Gui/*.hh")

# enable warnings
ADD_DEFINITIONS(-Wall)

################################################################################
# External Libraries
################################################################################

# GLEW
FIND_PACKAGE(GLEW REQUIRED)
ADD_DEFINITIONS(${GLEW_DEFINES})
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})
SET(LIBRARIES ${LIBRARIES} ${GLEW_LIBRARIES})

# Qt
SET(QT_USE_QTOPENGL TRUE)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
SET(LIBRARIES ${LIBRARIES} ${QT_LIBRARIES})
QT4_WRAP_CPP(MOC_SOURCE_FILES ${MOC_HEADER_FILES})
SET(SOURCE_FILES ${SOURCE_FILES} ${MOC_SOURCE_FILES})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# GLM
FIND_PACKAGE(GLM REQUIRED)
INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIR})

# ACGL
FIND_PACKAGE(ACGL REQUIRED)
ADD_DEFINITIONS(${ACGL_DEFINES})
INCLUDE_DIRECTORIES(${ACGL_INCLUDE_DIR})
SET(LIBRARIES ${LIBRARIES} ${ACGL_LIBRARIES})

# OpenGL
FIND_PACKAGE(OpenGL)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
SET(LIBRARIES ${LIBRARIES} ${OPENGL_LIBRARIES})

################################################################################
# Final Definition
################################################################################

# Define the Project, add all required sources and dependencies to it
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}${COMPILE_POSTFIX} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}${COMPILE_POSTFIX} ${LIBRARIES})

