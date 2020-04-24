cmake_minimum_required(VERSION 3.16)
project(tp3)

set(CMAKE_CXX_STANDARD 11)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_gl_LIBRARY: ${OPENGL_gl_LIBRARY}")
find_package(GLUT REQUIRED)

add_executable(lumiere lumiere.c)
target_include_directories(lumiere PUBLIC ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
target_link_libraries(lumiere PUBLIC ${OPENGL_opengl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES})
#target_link_libraries(helloteapot OpenGL::OpenGL OpenGL::GLU GLUT::GLUT)

add_executable(textureDemo textureDemo.c)
target_include_directories(textureDemo PUBLIC ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
target_link_libraries(textureDemo PUBLIC ${OPENGL_opengl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES})

add_executable(texture texture.c pnm_io.c)
target_include_directories(texture PUBLIC ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})
target_link_libraries(texture PUBLIC ${OPENGL_opengl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARIES})