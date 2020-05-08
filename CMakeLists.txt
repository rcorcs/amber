cmake_minimum_required(VERSION 3.4.3)

project(AMBER)

include_directories($(CMAKE_CURRENT_SOURCE_DIR)/include)
#link_libraries("-lGL -lGLU -lm -lGLEW -lglfw -lglut -lpng -ljpeg -lgtest -lpthread")
link_libraries("-lm -lGL -lGLEW -lglfw -lpng -ljpeg -lgtest -lpthread")

add_subdirectory(lib)
add_subdirectory(experiments)
add_subdirectory(unittest)
