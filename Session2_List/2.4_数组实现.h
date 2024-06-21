#ifndef LEARNING_2_4_数组实现_H
#define LEARNING_2_4_数组实现_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LIST_INIT_SIZE 100 // 一般来讲，宏变量命名为全大写

/**
 * 运行配置：List_order
 * 使用结构体数组实现线性表的顺序存储，以多项式为例
 * wswsl23 2024.06.20
 */

typedef struct Polynomial{
    float p; // 系数
    int e;   // 指数
    // 一般来讲，除了for循环之类的使用ijk以外，不建议使用单字母变量
};

typedef struct Sqlist{
    // struct Polynomial elem[LIST_INIT_SIZE];
    struct Polynomial *elem; // 动态分配 (struct Polynomial*)malloc(sizeof(struct Polynomial)*LIST_INIT_SIZE);
    int length;
};
// 相等判断
int IsEqual(struct Polynomial e, struct Polynomial f) {
    if (e.e==f.e && e.p==f.p)
        return 1;
    return 0;
}

// 打印
void PrintPoly(struct Polynomial e){
    printf("%.2fx^%d",e.p,e.e);
}

// 初始化线性表
int InitList_Sq(struct Sqlist *L){
    L->elem = (struct Polynomial*)malloc(sizeof(struct Polynomial)*LIST_INIT_SIZE);
    if(!L->elem)
        exit(-2);
    L->length = 0;
    return 1;
}

// 释放线性表
void DestroyList(struct Sqlist *L){
    if (L->elem)
        free(L->elem);
    L->length = 0; // 老师没有这一步，个人认为需要
}

// 清空线性表
void ClearList(struct Sqlist *L){
    L->length = 0;
}

// 获取线性表长度
int GetLength(struct Sqlist L){
    return L.length;
}

// 线性表是否为空
int IsEmpty(struct Sqlist L){
    if (L.length==0)
        return 1;
    return 0;
}

// 获取对应位置元素
int GetElem(struct Sqlist L,int i,struct Polynomial *e){
/**
 * 不知道是老师的个人习惯还是C语言的习惯，个人在使用Python时，倾向于return取出来的值，而这里是返回成功/失败，使用传参进行值的传递。
 * 个人推测，Python取值失败可以返回None(null)，但是C语言变量类型严格，因此无法成功返回值，失败返回空(类型不同)？未求证，欢迎大家指点。
 */
    // if (i<1 || i>L.length)
    if (IsEmpty(L) || i>GetLength(L))
        /**
         * 虽然 L.length和GetLength(L) 效果一样，但在一些复杂的情况下，为了安全不会开放L.length的使用，避免随意地修改结构体。
         * 并且，通过GetLength(L)之类的接口调用，有助于函数的封装，更容易维护和修改。
         * 例如，如果修改 .length 变量名，只需修改GetLength()中的名称。
         */
        return 0;
    *e = L.elem[i]; //虽然老师用的是i-1，但是个人对于i-1的操作倾向于在该函数外进行，使本函数和数组的取值方法保持一致
    return 1;
}

// 顺序表的查找
int LocateElem(struct Sqlist L,struct Polynomial e){
    struct Polynomial f;
    for (int i=0;i<GetLength(L);i++){
        // 结构体不可直接比较，需要自定义函数实现
        if (GetElem(L,i,&f) && IsEqual(e,f))
            return i;
    }
    return -1;
}

// 顺序表的插入
int ListInsert_Sq(struct Sqlist *L,int index,struct Polynomial e){ // 老师用的i，容易在用for的时候不注意产生问题。我改为了index
    // 判断 index 合法 / 剩余空间
    int length = GetLength(*L);
    if (index<0 || index>length || length>=LIST_INIT_SIZE)
        return 0;

    // 插入
    for (int i=length;i>index;i--){
        L->elem[i] = L->elem[i-1];
    }
    L->elem[index]=e;
    L->length++;
    return 1;
}

// 顺序表的删除
int ListDelete_Sq(struct Sqlist *L,int index){ // 老师用的i，容易在用for的时候不注意产生问题。我改为了index
    // 判断 index 合法
    int length = GetLength(*L);
    if (index<0 || index>length)
        return 0;

    // 删除
    for (int i=index;i<length;i++){
        L->elem[i] = L->elem[i+1];
    }
    L->length--;
    return 1;
}

// 打印多项式
void Print_Sq(struct Sqlist L){
    for (int i=0;i<GetLength(L)-1;i++){
        PrintPoly(L.elem[i]);
        printf(" + ");

    }
    if (GetLength(L)-1>=0){
        PrintPoly(L.elem[GetLength(L)-1]);
        printf("\n");
    }

}

#endif //LEARNING_2_4_数组实现_H
