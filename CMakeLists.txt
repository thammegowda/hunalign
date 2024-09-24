cmake_minimum_required(VERSION 3.10)

# Project name
project(hunalign)

# Set the source and include directories
#set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/hunalign)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/include)

# Set the C++ compiler
set(CMAKE_CXX_COMPILER g++)
# Set the compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O9 -ffast-math -funroll-loops")

# Set the include directories
include_directories(${INCLUDE_DIR})

# Set the libraries to link against
set(LIBS -lstdc++)
# Set the external libraries to link against
set(EXT_LIBS "")


# Collect all source files
#file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/hunalign/alignerTool.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/alignment.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/bloom.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/bookToMatrix.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/cooccurrence.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/cooccurrenceTool.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/dictionary.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/main.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/networkFlow.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/oldAlignTest.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/trailPostprocessors.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/translate.cpp
    ${CMAKE_SOURCE_DIR}/src/hunalign/wordAlignment.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/stringsAndStreams.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/argumentsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/timer.cpp
)

# Add the library
add_library(hunalign STATIC ${SOURCES})
#target_link_libraries(hunalign ${EXT_LIBS})

# executable: hunalign target is taken by the library,
# so hunalign_exe is the executable but the output file name should be hunalign instead of hunalign_exe
add_executable(hunalign_exe ${CMAKE_SOURCE_DIR}/src/hunalign/main.cpp)
set_property(TARGET hunalign_exe PROPERTY OUTPUT_NAME hunalign)

# Link the library to the executable
target_link_libraries(hunalign_exe PUBLIC hunalign ${LIBS})
