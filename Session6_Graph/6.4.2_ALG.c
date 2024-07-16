#include <stdio.h>
#include <stdlib.h>
#define MVNUM 100
/**
 * 运行配置 AMGraph
 * 邻接矩阵实现图
 * wswsl23 2024.07.16
 */
typedef char VerTexType;
typedef int OtherInfo;

typedef struct ArcNode{
    int adjvex;
    struct ArcNode *next;
    OtherInfo info;
}ArcNode;

typedef struct VNode{
    VerTexType data;
    ArcNode *firstarc;
}VNode,AdjList[MVNUM];

typedef struct {
    AdjList vertices;
    int vexnum;
    int arcnum;
}ALGraph;

void CreatDG(ALGraph *G,int vexnum,int arcnum,VerTexType vexs[],int arcs[][2]){
    G->vexnum=vexnum;
    G->arcnum=arcnum;
    for (int i=0;i<vexnum;i++){
        G->vertices[i].data=vexs[i];
        G->vertices[i].firstarc=NULL;
    }
    ArcNode *arc;
    for (int i=0;i<arcnum;i++){
        arc = (ArcNode*)malloc(sizeof(ArcNode));
        if (!G->vertices[arcs[i][0]].firstarc){
            G->vertices[arcs[i][0]].firstarc = arc;
            arc->next = NULL;
        }
        else{
            arc->next = G->vertices[arcs[i][0]].firstarc;
            G->vertices[arcs[i][0]].firstarc = arc;
        }
        arc->adjvex = arcs[i][1];
    }

};

void PrintDG(ALGraph G){
    ArcNode *arc;
    for (int i=0;i<G.vexnum;i++){
        printf("%c -> ",G.vertices[i].data);
        arc = G.vertices[i].firstarc;
        while (arc){
            printf("%c -> ",G.vertices[arc->adjvex].data);
            arc = arc->next;
        }
        printf("NULL\n");
    }
}

void test(){
    ALGraph G;
    VerTexType vexs[] = {'a','b','c','d','e'};
    int arcs[7][2]={{0,1},{0,2},{0,3},{2,3},
                    {2,4},{1,4},{3,4}};
    CreatDG(&G,5,7,vexs,arcs);
    PrintDG(G);

}

int main(void){
    test();
    return 0;
}
