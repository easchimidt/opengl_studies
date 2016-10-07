cmake_minimum_required(VERSION 3.1.0)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /home/05367019978/Desenvolvimento/cmake_utils)

project(estudosOpenGL)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR/bin})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x") # força usar funcoes do c++11 presentes no g++ 4.6.3

find_library(GLFW_LIB libglfw3.a "/usr/local/lib/")

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

set(DEPENDENT_LIBRARY GL GLEW X11 Xrandr Xinerama Xxf86vm Xcursor)

add_executable(estudosOpenGL ../Window.cpp ../Window.h ../Scene.h ../Triangle.cpp ../Triangle.h
${PROJECT_SOURCE_DIR}/ArrayBuffer.cpp ${PROJECT_SOURCE_DIR}/ArrayBuffer.h)

target_link_libraries(estudosOpenGL ${GLFW_LIB} ${DEPENDENT_LIBRARY} )
