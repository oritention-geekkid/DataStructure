#include<stdio.h>
#include<stdlib.h>

/* 图复用代码（使用邻接矩阵法表示） */
#define maxVertaxNumber 12
#define NOEDGE 9999

typedef int weightType;
typedef char orderType;
typedef int vertax;

struct GNode {
    int NVertax;
    int NEdge;
    weightType G[maxVertaxNumber][maxVertaxNumber];
    orderType order[maxVertaxNumber];
};
typedef struct GNode *Graph;

struct ENode {
    vertax v1,v2;
    weightType weight;
};
typedef struct ENode *Edge;

Graph createMGraph(int NVertax) {
    Graph ret = (Graph)malloc(sizeof(struct GNode));
    ret->NVertax = NVertax;
    ret->NEdge = 0;
    for (int i=0;i<NVertax;i++) {
        ret->order[i] = i;
        for (int j=0;j<NVertax;j++) {
            ret->G[i][j] = NOEDGE;
        }
    }

    return ret;
}

void insertEgde(Graph graph, Edge edge) {
    graph->G[edge->v1][edge->v2] = edge->weight;
    graph->NEdge++;
}

/* 建图 
    输入格式为：
        Nv Ne
        v1 v2 weight
        v1 v2 weight
        ……
*/
Graph BuildGraph() {
    int Nv,Ne;
    scanf("%d %d",&Nv,&Ne);
    Graph graph = createMGraph(Nv);
    if(Ne!=0) {
        Edge tempEdge = (Edge)malloc(sizeof(tempEdge));
        for (int i=0;i<Ne;i++) {
            scanf("%d %d %d",&(tempEdge->v1),&(tempEdge->v2),&(tempEdge->weight));
            insertEgde(graph,tempEdge);
        }
    }
    return graph;
}
/* 图复用代码（使用邻接矩阵法表示） */