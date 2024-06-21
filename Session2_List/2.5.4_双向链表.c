#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/**
 * 运行配置：Dul_Node
 * 双向链表的插入和删除
 * wswsl23 2024.06.21
 */
typedef int ElemType;

typedef struct DulNode{
    ElemType data;
    struct DulNode *prior,*next;
}*DuLinkList;


// 插入
int ListInsert_DuL(DuLinkList *L,int index,ElemType e){
    DuLinkList head=*L;
    for (int i=0;i<index;i++){
        *L=(*L)->next;
        if (!*L)
            return 0;
    }
    DuLinkList s;
    s = (DuLinkList)malloc(sizeof(struct DulNode));
    s->data=e;
    s->next = (*L)->next;
    (*L)->next = s;
    s->prior = *L;
    if (s->next)
        s->next->prior = s;
    *L = head;
    return 1;
}

// 删除
int ListDelete_DuL(DuLinkList *L,int index,ElemType *e){
    DuLinkList head=*L;
    *L = (*L)->next;
    for (int i=0;i<index;i++){
        if (!*L)
            return 0;
        *L=(*L)->next;
    }
    (*L)->prior->next = (*L)->next;
    if ((*L)->next)
        (*L)->next->prior = (*L)->prior;
    *e = (*L)->data;
    *L = head;

    return 1;
}
// 打印链表
void Print_List(DuLinkList L){
    while (L->next){
        L = L->next;
        printf("%d -> ",L->data);
    }
}

void test(){
    DuLinkList L;
    L = (DuLinkList)malloc(sizeof(struct DulNode));
    L->next=NULL;
    L->prior=NULL;

    assert(ListInsert_DuL(&L,0,6));
    assert(ListInsert_DuL(&L,0,7));
    assert(ListInsert_DuL(&L,1,9));
    Print_List(L); // 7 -> 9 -> 6 ->
    printf("\n");

    int n;
    assert(ListDelete_DuL(&L,2,&n));
    assert(n==6);
    Print_List(L);
}

void main(){
    test();
}
