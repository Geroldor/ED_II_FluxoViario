#include "digraph.h"

typedef struct Dnode{
    char* nome;
    float x, y;
    Info info;
} dnode;

typedef struct Daresta{
    char* nome;
    char* ecep, dcep;
    int from, to;
    float vm, cmp;

} daresta;

typedef struct Digraph{
    int V, E, maxNodes;
    Lista nodes;
    Lista arestas;
} digraph;

Digraph createGraph(int nVert){
    digraph *g = malloc(sizeof(digraph));
    g->maxNodes = nVert;
    g->V = 0;
    g->E = 0;
    g->nodes = createList(nVert);
    g->arestas = createList(-1);
    return g;
}


int getMaxNodes(Digraph g){
    digraph *gr = (digraph*)g;
    return gr->maxNodes;
}

int getTotalNodes(Digraph g){
    digraph *gr = (digraph*)g;
    return gr->V;
}

Node addNode(Digraph g, char *nome, Info info){
    digraph *gr = (digraph*)g;
    dnode *n = malloc(sizeof(dnode));
    n->nome = nome;
    n->x = ((float*)info)[0];
    n->y = ((float*)info)[1];
    insert(gr->nodes, n, nome);
    gr->V++;
    return n;
}


Node getNode(Digraph g,  char *nome){
    digraph *gr = (digraph*)g;
    for(int i = 0; i < gr->V; i++){
        dnode *n = (dnode*)search(gr->nodes, nome);
        if(strcmp(n->nome, nome) == 0){
            return n;
        }
    }
    return NULL;
}

Info getNodeInfo(Digraph g, Node node){
    dnode *n = (dnode*)node;
    return n->info;
}

char *getNodeName(Digraph g, Node node){
    dnode *n = (dnode*)node;
    return n->nome;
}

void setNodeInfo(Digraph g, Node node, Info info){
    dnode *n = (dnode*)node;
    n->info = info;
}

Edge addEdge(Digraph g, Node from, Node to, Info info){
    digraph *gr = (digraph*)g;
    daresta *a = malloc(sizeof(daresta));
    a->from = from;
    a->to = to;
    a->ecep = ((char*)info)[0];
    a->dcep = ((char*)info)[1];
    a->vm = ((float*)info)[2];
    a->cmp = ((float*)info)[3];
    insert(gr->arestas, a, a->nome);
    gr->E++;
    return a;
}

Edge getEdge(Digraph g, Node from, Node to){
    digraph *gr = (digraph*)g;
    for(int i = 0; i < gr->E; i++){
        daresta *a = (daresta*)search(gr->arestas, a->nome);
        if(a->from == from && a->to == to){
            return a;
        }
    }
    return NULL;
}

Node getFromNode(Digraph g, Edge e){
    daresta *a = (daresta*)e;
    return a->from;
}

Node getToNode(Digraph g, Edge e){
    daresta *a = (daresta*)e;
    return a->to;
}

Info getEdgeInfo(Digraph g, Edge e){
    daresta *a = (daresta*)e;
    return a->ecep;
}

void setEdgeInfo(Digraph g, Edge e, Info info){
    daresta *a = (daresta*)e;
    a->ecep = info;
}

void removeEdge(Digraph g, Edge e){
    digraph *gr = (digraph*)g;
    remover(gr->arestas, e);
    gr->E--;
}

bool isAdjacent(Digraph g, Node from, Node to){
    digraph *gr = (digraph*)g;
    for(int i = 0; i < gr->E; i++){
        daresta *a = (daresta*)search(gr->arestas, a->nome);
        if(a->from == from && a->to == to){
            return true;
        }
    }
    return false;
}

void adjacentNodes(Digraph g, Node node, Lista nosAdjacentes){
    digraph *gr = (digraph*)g;
    for(int i = 0; i < gr->E; i++){
        daresta *a = (daresta*)search(gr->arestas, a->nome);
        if(a->from == node){
            insert(nosAdjacentes, a->to, a->nome);
        }
    }
}

void adjacentEdges(Digraph g, Node node, Lista arestaAdjacentes){
    digraph *gr = (digraph*)g;
    for(int i = 0; i < gr->E; i++){
        daresta *a = (daresta*)search(gr->arestas, a->nome);
        if(a->from == node){
            insert(arestaAdjacentes, a, a->nome);
        }
    }
}

void getNodeNames(Digraph g, Lista nomesNodes){
    digraph *gr = (digraph*)g;
    for(int i = 0; i < gr->V; i++){
        dnode *n = (dnode*)get(gr->nodes, i);
        insert(nomesNodes, n->nome, n->nome);
    }
}

void getEdges(Digraph g, Lista arestas){
    digraph *gr = (digraph*)g;
    for(int i = 0; i < gr->E; i++){
        daresta *a = (daresta*)get(gr->arestas, i);
        insert(arestas, a, a->nome);
    }
}

bool dfsAux(Digraph g, Node node, bool *visited, procEdge treeEdge, procEdge fowardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void* extra){
    digraph *gr = (digraph*)g;
    visited[node] = true;
    for(int i = 0; i < gr->E; i++){
        daresta *a = (daresta*)search(gr->arestas, a->nome);
        if(a->from == node){
            if(!visited[a->to]){
                if(!newTree(a, extra)){
                    return false;
                }
                if(!dfsAux(g, a->to, visited, treeEdge, fowardEdge, returnEdge, crossEdge, newTree, extra)){
                    return false;
                }
            }else{
                if(!returnEdge(a, extra)){
                    return false;
                }
            }
        }
    }
    return true;
}

bool dfs(Digraph g, Node node, procEdge treeEdge, procEdge fowardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void* extra){
    digraph *gr = (digraph*)g;
    bool *visited = malloc(gr->V * sizeof(bool));
    for(int i = 0; i < gr->V; i++){
        visited[i] = false;
    }
    return dfsAux(g, node, visited, treeEdge, fowardEdge, returnEdge, crossEdge, newTree, extra);
}

bool bfs(Digraph g, Node node, procEdge discoverNode, void *extra){
    digraph *gr = (digraph*)g;
    bool *visited = malloc(gr->V * sizeof(bool));
    for(int i = 0; i < gr->V; i++){
        visited[i] = false;
    }
    Lista q = createLista(gr->V);
    insert(q, node, getNodeName(g, node));
    visited[node] = true;
    while(!isEmpty(q)){
        Node n = pop(q);
        for(int i = 0; i < gr->E; i++){
            daresta *a = (daresta*)search(gr->arestas, a->nome);
            if(a->from == n){
                if(!visited[a->to]){
                    if(!discoverNode(a, extra)){
                        return false;
                    }
                    visited[a->to] = true;
                    insert(q, a->to, a->nome);
                }
            }
        }
    }
    return true;
}

void killDG(Digraph g){
    digraph *gr = (digraph*)g;
    free(gr->nodes);
    free(gr->arestas);
    free(gr);
}

void createSubgraph(Digraph g, Digraph sg, bool *nodes, bool *edges){
    digraph *gr = (digraph*)g;
    digraph *sgr = (digraph*)sg;
    for(int i = 0; i < gr->V; i++){
        if(nodes[i]){
            dnode *n = (dnode*)get(gr->nodes, i);
            addNode(sg, n->nome, n->info);
        }
    }
    for(int i = 0; i < gr->E; i++){
        if(edges[i]){
            daresta *a = (daresta*)get(gr->arestas, i);
            addEdge(sg, a->from, a->to, a->ecep);
        }
    }
}

Edge includeEdgeSDG(Digraph g, char *nomeSubGrafo, Edge e){
    digraph *gr = (digraph*)g;
    daresta *a = (daresta*)e;
    digraph *sgr = (digraph*)search(gr->nodes, nomeSubGrafo);
    return addEdge(sgr, a->from, a->to, a->ecep);
}

bool existsEdgeSDG(Digraph g, char *nomeSubGrafo, Edge e){
    digraph *gr = (digraph*)g;
    daresta *a = (daresta*)e;
    digraph *sgr = (digraph*)search(gr->nodes, nomeSubGrafo);
    return isAdjacent(sgr, a->from, a->to);
}

void excludeEdgeSDG(Digraph g, char *nomeSubGrafo, Edge e){
    digraph *gr = (digraph*)g;
    daresta *a = (daresta*)e;
    digraph *sgr = (digraph*)search(gr->nodes, nomeSubGrafo);
    removeEdge(sgr, a);
}

void adjacentEdgesSDG(Digraph g, char *nomeSubGrafo, Node node, Lista arestaAdjacentes){
    digraph *gr = (digraph*)g;
    digraph *sgr = (digraph*)search(gr->nodes, nomeSubGrafo);
    adjacentEdges(sgr, node, arestaAdjacentes);
}

void getAllNodesSDG(Digraph g, char *nomeSubGrafo, Lista nos){
    digraph *gr = (digraph*)g;
    digraph *sgr = (digraph*)search(gr->nodes, nomeSubGrafo);
    getNodeNames(sgr, nos);
}

void getAllEdgesSDG(Digraph g, char *nomeSubGrafo, Lista arestas){
    digraph *gr = (digraph*)g;
    digraph *sgr = (digraph*)search(gr->nodes, nomeSubGrafo);
    getEdges(sgr, arestas);
}
