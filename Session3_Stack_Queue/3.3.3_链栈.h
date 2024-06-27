#include <stdlib.h>
#include <assert.h>

/**
 * 运行配置：Stack_Node
 * 使用链表表示栈
 * wswsl23 2024.06.23
 */


// typedef int Elemtype;

typedef struct Stack_N{
    Elemtype data;
    struct Stack_N *next;
}*LinkStack;

// 初始化栈
void InitStack(LinkStack *S){
    *S = NULL;
}

// 栈空
int ListEmpty(LinkStack S){
    if (S)
        return 0;
    return 1;
}

// 入栈
int Push(LinkStack *S,Elemtype data){
    LinkStack Node;
    Node = (LinkStack)malloc(sizeof(struct Stack_N));
    if (!Node)
        return 0;
    Node->data = data;
    Node->next = *S;
    *S=Node;
    return 1;
}

// 出栈
int Pop(LinkStack *S,Elemtype *data){
    if (ListEmpty(*S))
        return 0;
    LinkStack Node = *S;
    *data = Node->data;
    *S = Node->next;
    free(Node);
    return 1;
}

// 取栈顶元素
Elemtype GetTop(LinkStack S){
    if (!ListEmpty(S))
        return S->data;
}
