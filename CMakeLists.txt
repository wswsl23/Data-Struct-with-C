cmake_minimum_required(VERSION 3.28)
project(learning C)

set(CMAKE_C_STANDARD 11)

add_executable(complex_num Session1/1.3_复数.c)

add_executable(List_order Session2/2.4_线性表_顺序.c
        Session2/2.4_线性表_顺序.h)
add_executable(Test_Polynomial
        Session2/2.4_线性表_顺序.h
        Session2/练习_一元多项式加减_顺序.c)

add_executable(List_Node Session2/2.5_线性表_链式.c)