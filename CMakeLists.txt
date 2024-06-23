cmake_minimum_required(VERSION 3.28)
project(learning C)

set(CMAKE_C_STANDARD 11)

add_executable(complex_num Session1/1.3_复数.c)

add_executable(List_order Session2_List/2.4_数组实现.c
        Session2_List/2.4_数组实现.h)
add_executable(Test_Polynomial Session2_List/2.4_数组实现.h
        Session2_List/练习_1_一元多项式加减.c)

add_executable(List_Node Session2_List/2.5.0_链表.c)
add_executable(Dul_Node Session2_List/2.5.4_双向链表.c)

add_executable(Stack Session3_Stack/3.3.2_栈的顺序表示.c)
add_executable(Calculator Session3_Stack/练习_2_算式.c
        Session3_Stack/3.3.3_链栈.h)

