cmake_minimum_required(VERSION 3.29)
project(TPFinal)

set(CMAKE_CXX_STANDARD 20)

add_executable(TPFinal main.cpp
        Huffman.cpp
        Huffman.h
        stb_image.h
        stb_image_write.h)
