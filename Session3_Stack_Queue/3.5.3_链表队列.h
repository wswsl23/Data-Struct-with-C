#include <stdlib.h>
#include <assert.h>

/**
 * 使用链表表示队列
 * wswsl23 2024.06.24
 */

// typedef int Elemtype;

// 单个节点
typedef struct Qnode{
    Elemtype data;
    struct Qnode *next;
}*QuenePtr;

// 队列
typedef struct {
    QuenePtr front;
    QuenePtr rear;
}LinkQueue;

// 初始化
int InitQueue(LinkQueue *Q){
    Q->front= Q->rear = (QuenePtr)malloc(sizeof(struct Qnode));
    if (!Q->front)
        return 0;
    Q->front->next=NULL;
    return 1;
}

// 销毁
int DestroyQueue(LinkQueue *Q){
    QuenePtr tmp;
    while (Q->front){
        tmp = Q->front;
        Q->front=Q->front->next;
        free(tmp);
    }
    return 1;
}

// 入队
int EnQueue(LinkQueue *Q,Elemtype e){
    QuenePtr tmp = (QuenePtr)malloc(sizeof(struct Qnode));
    if (!tmp)
        return 0;
    tmp->data=e;
    tmp->next=NULL;
    Q->rear->next = tmp;
    Q->rear = tmp;
    return 1;
}

// 出队
int DeQueue(LinkQueue *Q,Elemtype *e){
    if (Q->front==Q->rear)
        return 0;
    QuenePtr tmp = Q->front->next;
    *e = tmp->data;
    Q->front->next = tmp->next;
    if (Q->rear==tmp)
        Q->rear=Q->front;
    free(tmp);
    return 1;
}

// 取队头元素
Elemtype GetHead(LinkQueue Q){
    if (Q.front!=Q.rear)
        return Q.front->next->data;
}

// 长度
int QueueLength(LinkQueue Q){
    QuenePtr tmp = Q.front;
    int n=0;
    while (tmp!=Q.rear){
        tmp=tmp->next;
        n++;
    }
    return n;
}




