#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * 运行配置 Huffman
 * 哈夫曼树的构建
 * wswsl23 2024.07.11
 */

typedef struct {
    int weight;
    int parent;
    int lch;
    int rch;
}HuffmanNode,*HuffmanTree;

// s1最小，s2次小
void Select(HuffmanTree HT,int index,int *s1,int *s2){
    *s1=-1;
    *s2=-1;
    for (int i=1;i<=index;i++){
        if (HT[i].parent==0){
            if (*s1==-1)
                *s1=i;
            else if (HT[i].weight<HT[*s1].weight){
                *s2=*s1;
                *s1=i;
            }
            else if (*s2==-1 || HT[i].weight<HT[*s2].weight){
                *s2=i;
            }
        }
    }
}

void CreateHuffman(HuffmanTree *HT,int n,int weights[]){
    if (n<=1)
        return;

    int m = 2*n-1;
    *HT = malloc(sizeof(HuffmanNode)*(m+1));
    for (int i=1;i<=m;i++){
        (*HT)[i].lch=0;
        (*HT)[i].rch=0;
        (*HT)[i].parent=0;
    }
    for (int i=1;i<=n;i++)
        (*HT)[i].weight=weights[i-1];

    for (int i=n+1,s1,s2;i<=m;i++){
        Select(*HT,i-1,&s1,&s2);
        (*HT)[s1].parent=i;
        (*HT)[s2].parent=i;
        (*HT)[i].lch=s1;
        (*HT)[i].rch=s2;
        (*HT)[i].weight = (*HT)[s1].weight+(*HT)[s2].weight;
    }
}

void PrintHuffman(HuffmanTree HT,int n){
    printf("  \tweight\tparent\tlch\trch\n");
    for (int i=1;i<2*n;i++){
        printf("%d.\t  %d\t  %d\t  %d\t  %d\n",i,HT[i].weight,HT[i].parent,HT[i].lch,HT[i].rch);
    }
}

void test(){
    HuffmanTree HT;
    int weight[]={5,29,7,8,14,23,3,11};
    CreateHuffman(&HT,8,weight);
    PrintHuffman(HT,8);
    assert("请自行对比"==1);
}

int main(){
    test();
    return 0;
}