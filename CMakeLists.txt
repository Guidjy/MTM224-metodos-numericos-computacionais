cmake_minimum_required(VERSION 3.10.0)
project(metodos VERSION 0.1.0 LANGUAGES C)

add_executable(metodos 
    src/main.c
    src/zeros.c
    src/sistemas_lineares.c
)

target_include_directories(metodos PRIVATE ${PROJECT_SOURCE_DIR}/include)
