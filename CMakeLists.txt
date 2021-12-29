cmake_minimum_required(VERSION 3.12)
project(hw1)


add_subdirectory(ListGraph)
add_subdirectory(MatrixGraph)
add_subdirectory(ArcGraph)
add_subdirectory(SetGraph)


add_executable(main main.cpp)
target_include_directories(main PUBLIC ListGraph MatrixGraph ArcGraph SetGraph)

target_link_libraries(main ListGraph MatrixGraph ArcGraph SetGraph)

