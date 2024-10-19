cmake_minimum_required(VERSION 3.28)
project(compiladorMiniJava C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(compiler src/compiler.cpp
        src/sin/sin.cpp
        src/lex/lex.cpp
        src/ist/ist.cpp
)

add_executable(interpreter src/interpreter.cpp
        src/sin/sin.cpp
        src/lex/lex.cpp
        src/ist/ist.cpp
)