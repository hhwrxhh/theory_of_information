cmake_minimum_required(VERSION 3.12)

project(entropy_of_photo)
set(PROJECT_NAME entropy_of_photo)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME}
	src/main.cpp
	
	external/bitmap/bitmap_image.hpp
	external/stbi_image/stbi_image.h
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
