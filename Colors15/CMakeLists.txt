cmake_minimum_required(VERSION 3.5)

project(Tutorial15 VERSION 0.1 LANGUAGES CXX)

list(APPEND EXTRA_LIBS 
	${PROJECT_SOURCE_DIR}/../lib/glfw-3.3.8/lib/glfw3.lib
	${PROJECT_SOURCE_DIR}/../lib/glew-2.1.0/lib/Release/x64/glew32s.lib
	opengl32.lib
)

list(APPEND EXTRA_INCLUDES 
	"${PROJECT_SOURCE_DIR}/../lib/glfw-3.3.8/include"
	"${PROJECT_SOURCE_DIR}/../lib/glew-2.1.0/include"
	"${PROJECT_SOURCE_DIR}/../lib/stb/include"
	"${PROJECT_SOURCE_DIR}/../lib/glm"
	)

add_executable(Tutorial15
  main.cpp
  Shader.cpp
  Shader.h
  Camera.cpp
  Camera.h
)
target_link_libraries(Tutorial15 ${EXTRA_LIBS})
target_include_directories(Tutorial15 PUBLIC ${EXTRA_INCLUDES})
