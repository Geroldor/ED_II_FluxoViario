#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "digraph.h"


void via(char* filePath){
    FILE* file = fopen(filePath, "r");
    int size;
    fscanf(file, "%d", &size);
    Digraph d = digraph_create(size);

    char* c;
    while (1)
    {
       fscanf(file, "%s", c);
       if (strcmp(c, "v") == 0)
       {
        int id;
        float x, y;
        fscanf(file, "%d %f %f", &id, &x, &y);
        addNode(d, id, x, y);
       }
       if (strcmp(c, "e") == 0)
       {
        int i, j;
        char* lesq, ldir, nome;
        float cmp, vm;
        fscanf(file, "%d %d %s %s %f %f %s", &i, &j, &lesq, &ldir, &cmp, &vm, &nome);
        addEdge(d, i, j, lesq, ldir, cmp, vm, nome);
       }
       
       
    }
    
}