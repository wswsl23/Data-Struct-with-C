#include <stdlib.h>
#include <assert.h>
#define MAXQSIZE 100
/**
 * 运行配置：Queue
 * 使用数组表示队列
 * wswsl23 2024.06.24
 */


typedef int Elemtype;

typedef struct {
    Elemtype *base;
    int front;
    int rear;
}Queue;

// 初始化队列
int InitQueue(Queue *Q){
    Q->base = (Elemtype*)malloc(sizeof(Elemtype)*MAXQSIZE);
    if (!Q->base)
        return 0;
    Q->front=Q->rear=0;
    return 1;
}

// 队列长度
int QueueLength(Queue Q){
    return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
}

// 入队
int EnQueue(Queue *Q,Elemtype e){
    if ((Q->rear+1)%MAXQSIZE==Q->front)
        return 0;
    Q->base[Q->rear++] = e;
    Q->rear %= MAXQSIZE;
    return 1;
}

// 出队
int DeQueue(Queue *Q,Elemtype *e){
    if (Q->front==Q->rear)
        return 0;
    *e = Q->base[Q->front++];
    Q->front %= MAXQSIZE;
    return 1;
}

// 取队头元素
Elemtype GetHead(Queue Q){
    if (Q.front!=Q.rear)
        return Q.base[Q.front];
}

void test(){
    Queue Q;
    // 初始化
    assert(InitQueue(&Q));
    // 入队
    assert(EnQueue(&Q,2));
    assert(EnQueue(&Q,5));
    assert(EnQueue(&Q,17));
    // 队头 长度
    assert(GetHead(Q)==2);
    assert(QueueLength(Q)==3);
    // 出队
    int n;
    assert(DeQueue(&Q,&n));
    assert(n==2);
    assert(QueueLength(Q)==2);
}

int main(){
    test();
    return 0;
}


