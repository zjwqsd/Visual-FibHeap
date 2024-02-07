cmake_minimum_required(VERSION 3.27)
project(Visual-FibHeap)

set(CMAKE_CXX_STANDARD 17)
include_directories(D:\\PATH\\SDL2-MINGW\\x86_64-w64-mingw32\\include)
include_directories(include)
link_directories(D:\\PATH\\SDL2-MINGW\\x86_64-w64-mingw32\\lib)
add_executable(Visual-FibHeap
        src/main.cpp
        include/View/window.h
        include/pch.h
        src/window.cpp
        include/View/Context.h
        src/Context.cpp
        include/View/Renderer.h
        src/Renderer.cpp
        src/Controller.cpp
        include/Controller.h
        include/Model/Fibheap.h
        src/Fibheap.cpp
        include/Model/Model.h
        src/Model.cpp
)

target_link_libraries(Visual-FibHeap SDL2main SDL2 SDL2_image SDL2_ttf)