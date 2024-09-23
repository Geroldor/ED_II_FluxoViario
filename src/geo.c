#include "quadra.h"
#include <stdlib.h>


void geo(char* filePath)
{
    FILE* file = fopen(filePath, "r");
    char sw[5], cfill[22], cstrk[22], *com;
    while (1)
    {
        fscanf(file, "%s", com);
        if (feof(file)){break;}

        if (strcmp(com, "q") == 0)
        {
            char* cep;
            float x, y, w, h;
            fscanf(file, "%s %f %f %f %f", cep, &x, &y, &w, &h);
            Quadra q = createQuadra(cep, x, y, w, h);
        }
        if(strcmp(com, "cq") == 0)
        {
            fscanf(file, "%s %s %s", sw, cfill, cstrk);
        }   
    }
    
}