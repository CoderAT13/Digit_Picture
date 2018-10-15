# my cmake version
cmake_minimum_required(VERSION 3.0)

project(task_three)

find_package(OpenCV REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${OpenCV_INCLUDE_DIRS})

AUX_SOURCE_DIRECTORY(src DIR_SRCS)
MESSAGE(STATUS ¡°Src file: ${DIR_SRCS}¡±)

add_executable(a.out ${DIR_SRCS})

link_directories(${OpenCV_LIBRARY_DIRS})

target_link_libraries(a.out ${OpenCV_LIBS})