cmake_minimum_required(VERSION 3.13)
project(OpenGLTuto)

#add all source files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

#add all header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp)

include_directories(/usr/local/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/glfw3/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} glfw3 pthread X11 GL Xrandr Xi dl assimp)
