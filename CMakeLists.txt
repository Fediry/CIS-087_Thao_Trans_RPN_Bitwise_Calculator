cmake_minimum_required(VERSION 3.21)

# Config
project(Thao_Tran-RPN_Calculator VERSION 0.1.0 LANGUAGES C CXX)

# Sources
set(SOURCES
src/main.cpp
src/rpn_calc.cpp
src/tests.cpp
)
set(HEADERS
inc/main.h
inc/rpn_calc.h
inc/tests.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)

# Options
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-DDEBUG>)