cmake_minimum_required(VERSION 3.10)

project(poligons)

set(CMAKE_CXX_STANDARD 17)

add_executable(poligons
        src/main.cpp
        src/canvas.cpp src/canvas.h
        src/elements.cpp src/elements.h
	src/input_reader.cpp src/input_reader.h
	src/objects.cpp src/objects.h
	)