cmake_minimum_required(VERSION 3.31)
project(C_Calculator C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /Zi /Od /RTC1")

add_executable(C_Calculator main.c
        string_helper.c
        string_helper.h
        token.h
        token_list.c
        token_list.h
        tokenizer.c
        tokenizer.h
        parser.c
        parser.h
        solver.c
        solver.h)
