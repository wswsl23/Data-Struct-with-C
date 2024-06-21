#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int ElemType;

typedef struct Lnode{
    ElemType data;
    struct Lnode *next;
}LNode,*LinkList;

// 初始化链表
int InitList_L(LinkList *L){
    *L = (LinkList)malloc(sizeof(LNode));
    if (*L){
        (*L)->next = NULL;
        return 1;
    }
    return 0;
}

// 判断链表为空
int ListEmpty(LinkList L){
    if (L->next)
        return 0;
    return 1;
}

// 销毁链表
void DestroyList(LinkList L){
    LinkList tmp;
    while (L){
        tmp = L;
        L = L->next;
        free(tmp);
    }
}

// 清空链表
void ClearList(LinkList L){
    LinkList tmp,head;
    head  = L;
    while (L){
        tmp = L->next;
        L = L->next;
        free(tmp);
    }
    head->next = NULL;
}

// 求链表长度
int ListLength_L(LinkList L){
    int n=0;
    while (L->next){
        L = L->next;
        n++;
    }
    return n;
}

// 链表取值
int GetElem_L(LinkList L,int index,ElemType *e){
    L=L->next;
    for (int i=0;i<index;i++){
        if (!L)
            return 0;
        L=L->next;
    }
    *e = L->data;
    return 1;
}

// 链表查找
int LocateElem_L(LinkList L,ElemType e){
    int index=0;
    while (L->next){
        L = L->next;
        if (L->data==e)
            return index;
        index++;
    }
    return -1;
}

// 链表插入 模仿列表，index从0开始
int ListInsert_L(LinkList *L,int index,ElemType e){
    LinkList head=*L;
    for (int i=0;i<index;i++){
        *L=(*L)->next;
        if (!*L)
            return 0;
    }
    LinkList s;
    s = (LinkList)malloc(sizeof(LNode));
    s->data=e;
    s->next = (*L)->next;
    (*L)->next = s;
    *L = head;
    return 1;
}

// 删除节点
int ListDelete_L(LinkList *L,int index,ElemType *e){
    LinkList head=*L,pre=*L;
    *L = (*L)->next;
    for (int i=0;i<index;i++){
        if (!*L)
            return 0;
        pre = *L;
        *L=(*L)->next;
    }
    pre->next = (*L)->next;
    *e = (*L)->data;
    *L = head;

    return 1;
}

// 老师这里用的是控制台输入数据，我使用数组来替代

// 尾插法
void CreateList_R(LinkList *L,int nums[],int n){
    InitList_L(L);
    LinkList s;
    for (int i=n-1;i>=0;i--){
        s = (LinkList)malloc(sizeof(LNode));
        s->data = nums[i];
        s->next = (*L)->next;
        (*L)->next = s;
    }
}

// 头插法
void CreateList_H(LinkList *L,int nums[],int n){
    InitList_L(L);
    LinkList s=*L;
    for (int i=0;i<n;i++){
        s->next = (LinkList)malloc(sizeof(LNode));
        s = s->next;
        s->data = nums[i];
    }
    s->next = NULL;
}

// 打印链表
void Print_List(LinkList L){
    while (L->next){
        L = L->next;
        printf("%d -> ",L->data);
    }
}

void test(LinkList L){
    // 插入3个节点
    assert(ListInsert_L(&L,0,6));
    assert(ListInsert_L(&L,3,7));
    assert(ListInsert_L(&L,6,9));
    assert(ListLength_L(L)==7);

    Print_List(L); // 6 -> 3 -> 1 -> 7 -> 4 -> 2 -> 9 ->

    // 取值 查找
    int n;
    assert(GetElem_L(L,1,&n));
    assert(n==3);
    assert(LocateElem_L(L,4)==4);

    // 删除
    ListDelete_L(&L,2,&n);
    printf("%d",3);
}

int main(){
    LinkList L;
    int nums[4]={3,1,4,2};

    // 头插法
    CreateList_H(&L,nums,4);
    test(L);
    printf("\n");

    // 尾插法
    CreateList_R(&L,nums,4);
    test(L);
    return 0;
}