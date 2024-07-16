#include <stdio.h>

#define MVNUM 100

/**
 * 运行配置 AMGraph
 * 邻接矩阵实现图
 * wswsl23 2024.07.16
 */

typedef char VerTexType;
typedef int ArcType;
typedef struct {
    VerTexType vexs[MVNUM];
    ArcType arcs[MVNUM][MVNUM];
    int vexnum;
    int arcnum;
}AMGraph;

void CreatUDN(AMGraph *G,int vexnum,int arcnum,VerTexType vexs[],int arcs[][3]){
    G->vexnum = vexnum;
    G->arcnum = arcnum;
    for (int i=0;i<vexnum;i++){
        G->vexs[i]=vexs[i];
        for (int j=0;j<vexnum;j++)
            G->arcs[i][j]=-1;
    }

    for (int i=0;i<arcnum;i++){
        G->arcs[arcs[i][0]][arcs[i][1]]=arcs[i][2];
        G->arcs[arcs[i][1]][arcs[i][0]]=arcs[i][2];
    }
}

void PrintUDN(AMGraph G){
    printf(" \t");
    for (int i=0;i<G.vexnum;i++)
        printf("%c\t",G.vexs[i]);
    printf("\n");

    for (int i=0;i<G.vexnum;i++){
        printf("%c\t",G.vexs[i]);
        for (int j=0;j<G.vexnum;j++){
            printf("%d\t",G.arcs[i][j]);
        }
        printf("\n");
    }
}

void test(){
    AMGraph G;
    VerTexType vexs[] = {'a','b','c','d','e'};
    int arcs[7][3]={{0,1,5},{0,2,3},{0,3,8},{2,3,3},
                    {2,4,1},{1,4,2},{3,4,4}};
    CreatUDN(&G,5,7,vexs,arcs);
    PrintUDN(G);
}

int main(void){
    test();
    return 0;
}