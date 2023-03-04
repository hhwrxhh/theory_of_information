cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME entropy_of_photo)

add_executable(${PROJECT_NAME}
	src/main.cpp
	
	external/bitmap/bitmap_image.hpp
)

