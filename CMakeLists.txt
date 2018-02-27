cmake_minimum_required(VERSION 2.8.4)
project(Game)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

file(GLOB SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/engine/*.cpp
    ${PROJECT_SOURCE_DIR}/src/engine/ecs/*.cpp
)

file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${PROJECT_BINARY_DIR})

add_executable(Game 
    ${SOURCE_FILES}
)

target_link_libraries(Game 
    ${SDL2_LIBRARY}
    ${OPENGL_LIBRARY}
    ${GLEW_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)