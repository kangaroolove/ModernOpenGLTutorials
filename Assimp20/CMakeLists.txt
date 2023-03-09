cmake_minimum_required(VERSION 3.5)

project(Tutorial20 VERSION 0.1 LANGUAGES CXX)

list(APPEND EXTRA_LIBS 
	${PROJECT_SOURCE_DIR}/../lib/glfw-3.3.8/lib/glfw3.lib
	${PROJECT_SOURCE_DIR}/../lib/glew-2.1.0/lib/Release/x64/glew32s.lib
	${PROJECT_SOURCE_DIR}/../lib/Assimp/lib/assimp-vc140-mt.lib
	opengl32.lib
)

list(APPEND EXTRA_INCLUDES 
	"${PROJECT_SOURCE_DIR}/../lib/glfw-3.3.8/include"
	"${PROJECT_SOURCE_DIR}/../lib/glew-2.1.0/include"
	"${PROJECT_SOURCE_DIR}/../lib/stb/include"
	"${PROJECT_SOURCE_DIR}/../lib/glm"
	"${PROJECT_SOURCE_DIR}/../lib/Assimp/include"
	)

add_executable(Tutorial20
  main.cpp
  Shader.cpp
  Shader.h
  Camera.cpp
  Camera.h
)
target_link_libraries(Tutorial20 ${EXTRA_LIBS} ${ASSIMP_LIBRARIES})
target_include_directories(Tutorial20 PUBLIC ${EXTRA_INCLUDES})
