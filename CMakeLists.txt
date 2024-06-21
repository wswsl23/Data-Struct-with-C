cmake_minimum_required(VERSION 3.28)
project(learning C)

set(CMAKE_C_STANDARD 11)

add_executable(complex_num Session1/1.3_复数.c)

add_executable(List_order Session2_List/2.4_数组实现.c
        Session2_List/2.4_数组实现.h)
add_executable(Test_Polynomial
        Session2_List/2.4_数组实现.h
        Session2_List/练习_一元多项式加减.c)

add_executable(List_Node Session2_List/2.5.0_链表.c)

add_executable(Dul_Node Session2_List/2.5.4_双向链表.c)