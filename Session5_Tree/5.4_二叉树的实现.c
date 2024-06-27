#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * 运行配置 BinaryTree
 * 二叉树的实现，包含：
 *  先序递归遍历；中序非递归遍历；层次遍历；层次建立树
 * wswsl23 2024.06.27
 */

// 树的结构定义
typedef struct BinaryTree{
    int data;
    struct BinaryTree *left,*right;
}*TreeNode,*Elemtype;
#include "../Session3_Stack_Queue/3.3.3_链栈.h"
#include "../Session3_Stack_Queue/3.5.3_链表队列.h"

// 先序递归
void PreRecursion(TreeNode root){
    if (root){
        printf("%d ",root->data);
        PreRecursion(root->left);
        PreRecursion(root->right);
    }
}


// 中序非递归
void InorderTraverse(TreeNode root){
    TreeNode p=root;
    LinkStack Stack;
    InitStack(&Stack);
    while (p || !ListEmpty(Stack)){
        if (p){
            Push(&Stack,p);
            p = p->left;
        }
        else{
            Pop(&Stack,&p);
            printf("%d ",p->data);
            p = p->right;
        }
    }
    printf("\n");
}


// 层次遍历
void LevelOrder(TreeNode root){
    LinkQueue Queue;
    InitQueue(&Queue);

    TreeNode p=root;
    EnQueue(&Queue,p);
    while (Queue.front!=Queue.rear){
        DeQueue(&Queue,&p);
        if (p){
            printf("%d ",p->data);
            EnQueue(&Queue,p->left);
            EnQueue(&Queue,p->right);
        }
    }
    printf("\n");
}

// 初始化树
int InitTree(TreeNode *root){
    *root = (TreeNode)malloc(sizeof(struct BinaryTree));
    if (!*root)
        return 0;
    (*root)->left=NULL;
    (*root)->right=NULL;
    return 1;
}

// 按照层次遍历创建树
int CreateTree(TreeNode *root,int data[],int n){
    LinkQueue Queue;
    InitQueue(&Queue);

    TreeNode p;
    (*root)->data=data[0];
    EnQueue(&Queue,*root);

    for (int i=1;i<n;i+=2){
        DeQueue(&Queue,&p);
        // 左子树
        if (data[i]==-1)
            p->left=NULL;
        else{
            InitTree(&p->left);
            p->left->data=data[i];
            EnQueue(&Queue,p->left);
        }
        // 右子树
        if (data[i+1]==-1)
            p->right=NULL;
        else{
            InitTree(&p->right);
            p->right->data=data[i+1];
            EnQueue(&Queue,p->right);
        }
    }

    return 1;
}

void test(){
    TreeNode root;
    int data[]={1,2,3,4,-1,5,-1,6,7,8,-1};
    assert(InitTree(&root));
    assert(CreateTree(&root,data,11));
    PreRecursion(root);  // 1 2 4 6 7 3 5 8
    printf("\n");
    InorderTraverse(root); // 6 4 7 2 1 8 5 3
    LevelOrder(root); // 1 2 3 4 5 6 7 8
}

int main(){
    test();
    return 0;
}