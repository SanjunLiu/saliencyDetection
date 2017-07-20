cmake_minimum_required(VERSION 2.8.0)
project(saliency_detection)
option(OPEN_DEBUG "whether to open debug" OFF)

## gcc g++ >=4.8
SET(CMAKE_C_COMPILER "/usr/local/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/local/bin/g++")
include_directories(/usr/lib/gcc/x86_64-redhat-linux/4.4.4/include)

include_directories(./include)

find_package(OpenCV)
if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "opencv not found")
endif()

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fPIC")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fPIC")

set(SRC_FILES
    ./src/PreGraph.cpp
    ./src/SLIC.cpp
    )

add_library(slDetection SHARED ${SRC_FILES})
target_link_libraries(slDetection ${OpenCV_LIBS})

set(TEST_FILES ./test/main.cpp)

add_executable(salencyDetection ${TEST_FILES})
target_link_libraries(salencyDetection
    slDetection
    ${OpenCV_LIBS})
