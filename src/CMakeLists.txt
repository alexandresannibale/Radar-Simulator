cmake_minimum_required(VERSION 3.22.1)

project(radarSimulator)

add_executable(${PROJECT_NAME} main.cpp )

add_subdirectory(simLib)
add_subdirectory(test)


target_link_libraries(${PROJECT_NAME} simLib)

