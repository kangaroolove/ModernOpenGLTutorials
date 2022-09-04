cmake_minimum_required(VERSION 3.5)

project(Tutorial2 VERSION 0.1 LANGUAGES CXX)

list(APPEND EXTRA_LIBS 
	${PROJECT_SOURCE_DIR}/lib/glfw-3.3.8/lib/glfw3.lib
	${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/lib/Release/x64/glew32s.lib
	opengl32.lib
)

list(APPEND EXTRA_INCLUDES 
	"${PROJECT_SOURCE_DIR}/lib/glfw-3.3.8/include"
	"${PROJECT_SOURCE_DIR}/lib/glew-2.1.0/include")

add_executable(Tutorial2
  main.cpp
)
target_link_libraries(Tutorial2 ${EXTRA_LIBS})
target_include_directories(Tutorial2 PUBLIC ${EXTRA_INCLUDES})
