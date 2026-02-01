cmake_minimum_required(VERSION 3.10.0)
project(PaintTool VERSION 0.1.0)

include_directories("./include")
link_directories("./lib")

link_libraries(SDL3)

add_executable(PaintTool "./src/main.cpp")