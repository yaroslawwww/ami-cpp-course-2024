cmake_minimum_required(VERSION 3.5)

project(cpp-hse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address  -g -O3")
add_executable(image_processor
        cmdlineparser.cpp
        bmp.cpp
        image_processor.cpp
        filters/base_filter.cpp
        producer.cpp
        pipeline_factory.cpp
        filters/crop.cpp
        filters/edge.cpp
        filters/grayscale.cpp
        filters/negative.cpp
        filters/sharpening.cpp
)
