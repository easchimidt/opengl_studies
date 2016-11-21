cmake_minimum_required(VERSION 3.6)
project(estudosOpenGL)

find_package(glfw3 3.2.1 REQUIRED)
find_package(GLM REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}" )


set(SOURCE_FILES stb_image.h Window.cpp Window.h Scene.h
        ArrayBuffer.cpp ArrayBuffer.h IndexBuffer.cpp IndexBuffer.h Shader.cpp Shader.h
        Mesh.cpp Mesh.h MeshBuilder.cpp MeshBuilder.h
        RotatingSquare.h RotatingSquare.cpp MeshFactory.cpp MeshFactory.h Utils.h)
add_executable(estudosOpenGL ${SOURCE_FILES})
target_link_libraries(estudosOpenGL glfw glm "-framework OpenGL")