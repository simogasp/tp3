cmake_minimum_required(VERSION 3.10)
project(tp3 VERSION 2023.1.0 LANGUAGES CXX)

option(BUILD_TEAPOT "Build teapot sample" OFF)
option(ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

set(CMAKE_CXX_STANDARD 17)

include(CheckIPOSupported)
check_ipo_supported(RESULT result)
message(STATUS "IPO supported: ${result}")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${result})

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_gl_LIBRARY: ${OPENGL_gl_LIBRARY}")

if(MSVC)
    set(GLUT_ROOT_PATH "${CMAKE_SOURCE_DIR}/freeglut")
    message(STATUS "GLUT_ROOT_PATH: ${GLUT_ROOT_PATH}")
endif()
find_package(GLUT REQUIRED)
message(STATUS "GLUT_FOUND: ${GLUT_FOUND}")
message(STATUS "GLUT_INCLUDE_DIR: ${GLUT_INCLUDE_DIR}")
message(STATUS "GLUT_LIBRARIES: ${GLUT_LIBRARIES}")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(MY_COMPILE_OPTIONS "-Wall;-Wextra;-pedantic;-Wno-comment;-Wshadow;-Wnon-virtual-dtor;-Wpedantic;-Wconversion;-Wmisleading-indentation;-Wsign-conversion")
    if(ENABLE_WARNINGS_AS_ERRORS)
        list(APPEND MY_COMPILE_OPTIONS "-Werror")
    endif()
elseif(MSVC)
    set(MY_COMPILE_OPTIONS "/W4;/permissive-")
    if(ENABLE_WARNINGS_AS_ERRORS)
        list(APPEND MY_COMPILE_OPTIONS "/WX")
    endif()
endif()

if(APPLE)
    list(APPEND MY_COMPILE_OPTIONS "-Wno-deprecated-declarations")
endif()

add_executable(lumiere lumiere.cpp)
#target_include_directories(lumiere PUBLIC ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
#target_link_libraries(lumiere PUBLIC ${OPENGL_opengl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES})
target_link_libraries(lumiere OpenGL::GL OpenGL::GLU GLUT::GLUT)


target_compile_options(lumiere PRIVATE ${MY_COMPILE_OPTIONS})

if(MSVC)
    target_compile_definitions(lumiere PUBLIC -DNOMINMAX)
endif()

if(BUILD_TEAPOT)
    add_executable(teapot teapotLight.cpp)
    #target_include_directories(teapot PUBLIC ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
    #target_link_libraries(teapot PUBLIC ${OPENGL_opengl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES})
    target_link_libraries(teapot OpenGL::GL OpenGL::GLU GLUT::GLUT)

    target_compile_options(teapot PRIVATE ${MY_COMPILE_OPTIONS})

    if(MSVC)
        target_compile_definitions(teapot PUBLIC -DNOMINMAX)
    endif()
endif()