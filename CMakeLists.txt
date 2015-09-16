cmake_minimum_required(VERSION 3.2)
project(Project)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Project_SOURCE_DIR}/cmake")

find_package(AssImp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIR})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

set(GLEW_INCLUDE_DIR $ENV{GLEW_INCLUDE_DIR})
set(GLEW_LIBRARY $ENV{GLEW_LIBRARY})
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

include_directories(include)

file(GLOB_RECURSE  Project_SRC
    "src/*.cpp"
)

add_executable(project ${Project_SRC})

target_link_libraries(project ${ASSIMP_LIBRARY})
target_link_libraries(project ${SDL2_LIBRARY})
target_link_libraries(project ${SDL2_IMAGE_LIBRARY})
target_link_libraries(project ${GLEW_LIBRARIES})
target_link_libraries(project ${OPENGL_LIBRARIES})

MACRO(MAKE_WINDOWS_PATH pathname)
  STRING(REPLACE "/" "\\" ${pathname} "${${pathname}}")
  SET(${pathname} \"${${pathname}}\")
ENDMACRO(MAKE_WINDOWS_PATH)

set(EXEC_DIR "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")
MAKE_WINDOWS_PATH(EXEC_DIR)
add_custom_command( TARGET project POST_BUILD
	COMMAND copy "$ENV{SDL2_IMAGE}\\lib\\x86\\*.dll" ${EXEC_DIR}
	COMMAND copy "$ENV{SDL2}\\lib\\x86\\*.dll" ${EXEC_DIR}
	COMMAND copy "$ENV{GLEW_DLL}" ${EXEC_DIR}
)

set(needed_features
    cxx_strong_enums
    cxx_auto_type)
target_compile_features(project PRIVATE ${needed_features})