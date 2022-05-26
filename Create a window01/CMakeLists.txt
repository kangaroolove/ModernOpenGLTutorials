cmake_minimum_required(VERSION 3.5)

project(Tutorial1 VERSION 0.1 LANGUAGES CXX)

list(APPEND EXTRA_LIBS ${PROJECT_SOURCE_DIR}/lib/freeglut-3.2.2/lib/freeglutd.lib)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/lib/freeglut-3.2.2/include")

add_executable(Tutorial1
  main.cpp
)
target_link_libraries(Tutorial1 ${EXTRA_LIBS})
target_include_directories(Tutorial1 PUBLIC ${EXTRA_INCLUDES})
