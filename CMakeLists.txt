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

add_executable(Stack Session3_Stack_Queue/3.3.2_栈的顺序表示.c)
add_executable(Calculator Session3_Stack_Queue/练习_2_算式.c
        Session3_Stack_Queue/3.3.3_链栈.h)

add_executable(Queue Session3_Stack_Queue/3.5.2_数组队列.c)

add_executable(KMP Session4_KMP/4.3_KMP_病毒.c)

add_executable(BinaryTree Session5_Tree/5.4_二叉树的实现.c
        Session3_Stack_Queue/3.3.3_链栈.h
        Session3_Stack_Queue/3.5.3_链表队列.h)

add_executable(Huffman Session5_Tree/5.7_哈夫曼树.c)

add_executable(AMGraph Session6_Graph/6.4.1_邻接矩阵.c)
add_executable(ALGraph Session6_Graph/6.4.2_ALG.c)