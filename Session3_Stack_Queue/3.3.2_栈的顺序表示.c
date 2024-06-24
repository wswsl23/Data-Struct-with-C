#include <stdlib.h>
#include <assert.h>

#define MAXSIZE 100

/**
 * 运行配置：Stack
 * 使用数组表示栈
 * wswsl23 2024.06.23
 */

typedef char Elemtype;

typedef struct {
    Elemtype *top;
    Elemtype *base;
    int size;
}Stack;

// 初始化栈
int InitStack(Stack *S){
    S->base = (Elemtype*)malloc(MAXSIZE*sizeof(Elemtype));
    if (!S->base)
        return 0;
    S->top = S->base;
    S->size = MAXSIZE;
    return 1;
}

// 判断栈空
int StackEmpty(Stack S){
    if (S.base==S.top)
        return 1;
    return 0;
}

// 求栈长度
int StackLength(Stack S){
    return S.top-S.base;
}

// 清空栈
void ClearStack(Stack *S){
    if (S->base)
        S->top=S->base;
}

// 销毁栈
void DestroyStack(Stack *S){
    if (S->base)
        free(S->base);
    S->size = 0;
    S->base = S->top = NULL;
}

// 入栈
int Push(Stack *S,Elemtype data){
    if (StackLength(*S)==S->size)
        return 0;
    *(S->top++) = data;
    return 1;
}

// 出栈
int Pop(Stack *S,Elemtype *data){
    if (StackEmpty(*S))
        return 0;
    *data = *(--S->top);
    return 1;
}

void test(){
    Stack S;
    InitStack(&S);
    Elemtype data='a';
    assert(Push(&S,data));
    assert(Push(&S,data));
    data='b';
    assert(Push(&S,data));

    assert(Pop(&S,&data));
    assert(data=='b');
    assert(Pop(&S,&data));
    assert(data=='a');

}

void main(){
    test();
}