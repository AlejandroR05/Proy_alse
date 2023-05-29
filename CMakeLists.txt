cmake_minimum_required( VERSION 3.10 )
project( proyecto )
add_executable( ${PROJECT_NAME} main.cpp sensores.h)
target_link_libraries(${PROJECT_NAME} sqlite3)
