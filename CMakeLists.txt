cmake_minimum_required(VERSION 3.7)
project(ImacGL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


file(GLOB HEADER_FILES ${YOUR_DIRECTORY}include/*.h )

file(GLOB SOURCE_FILES ${YOUR_DIRECTORY}src/*.cpp )

file(GLOB_RECURSE SHADER_FILES ${YOUR_DIRECTORY}/shaders/*.glsl)

set(OUTPUT_DIR ${YOUR_DIRECTORY}bin)

set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIR})

include_directories( ${YOUR_DIRECTORY}lib/glimac/include  ${YOUR_DIRECTORY}lib/third-party/include)

add_subdirectory(lib/glimac)
set(LIB_LIST glimac -lmingw32 -lSDLmain -lSDL -lfreeglut -lglew32s -lopengl32 )

add_executable(opengl ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES} src/Object3D.cpp include/Object3D.h src/GameManager.cpp include/GameManager.h include/ShaderProgram.h src/Niveau.cpp include/Niveau.h src/Mesh3D.cpp include/Mesh3D.h src/Demon3D.cpp include/Demon3D.h include/Time.h src/Time.cpp src/Oscillation.cpp include/Oscillation.h src/Player.cpp include/Player.h src/MeshShared.cpp include/MeshShared.h src/Texture.cpp include/Texture.h src/Interface.cpp include/Interface.h)
target_link_libraries(opengl ${LIB_LIST})




