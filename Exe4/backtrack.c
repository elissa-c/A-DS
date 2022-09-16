#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <windows.h>
//#include "AdjecList.h"


typedef struct AdjacencyListItem
{
    int j;
    struct AdjacencyListItem *next;
} ALI;

ALI **AdjacencyList;
int AdjacencyListCount;

void addALEdge(int i, int j);

void initAList(int n)
{
    int i, j;

    AdjacencyList = (ALI **)calloc(n, sizeof(ALI *));
    AdjacencyListCount = n;
    for (int z=0; z<n; z++) {
        AdjacencyList[z] = 0;
    }
}

void addALEdge(int i, int j)
{
    if (AdjacencyList == NULL)
        return;

    ALI *newEdge = (ALI *)calloc(1, sizeof(ALI));

    newEdge->j = j;

    if (AdjacencyList[i] == 0)
    {
        AdjacencyList[i] = newEdge;
        return;
    }

    ALI *current = AdjacencyList[i];

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newEdge;

    return;
}

void freeAdjacencyList()
{
    if (AdjacencyList == NULL)
        return;

    int i;

    for (i = 0; i < AdjacencyListCount; i++)
    {
        ALI *current = AdjacencyList[i], *prev;

        while (current != NULL)
        {
            prev = current;
            current = prev->next;
            free(prev);
        }
    }

    free(AdjacencyList);
}

uint8_t checkALEdge(int i, int j)
{
    ALI *current;

    current = AdjacencyList[i];

    while (current != NULL)
    {
        if (current->j == j)
            return 1;

        current = current->next;
    }

    return 0;
}

void removeALEdge(int i, int j)
{
    if (AdjacencyList == NULL)
        return;

    if (AdjacencyList[i] == NULL)
        return;

    ALI *current = AdjacencyList[i], *prev;

    if (current->j == j)
    {
        current->j = -1;
        return;
    }

    while (current != NULL && current->j != j)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return;
    
    current->j = -1;
    
    return;
}



clock_t algoStart;

int8_t hamiltonianCycle();
int8_t findHamiltonianCycle(int *path, int currentPos);
int8_t checkPathArray(int pos, int v, int *path);
void printPath(int *path);

int8_t hamiltonianCycle()
{
    int i, *path = (int *)malloc(sizeof(int) * AdjacencyListCount);

    for (i = 0; i < AdjacencyListCount; i++)
        path[i] = -1;

    path[0] = 0;

    algoStart = clock();

    if (findHamiltonianCycle(path, 1) == 0)
    {
        return 0;
    }

    // printPath(path);

    free(path);
    return 1;
}

int8_t findHamiltonianCycle(int *path, int currentPos)
{
    clock_t runtime = clock() - algoStart;

    

    if (currentPos == AdjacencyListCount)
    {
        if (checkALEdge(path[currentPos - 1], path[0]))
            return 1;
        else
            return 0;
    }

    ALI *current = AdjacencyList[path[currentPos - 1]];

    while (current != NULL)
    {
        if (checkPathArray(currentPos, current->j, path))
        {
            path[currentPos] = current->j;

            if(findHamiltonianCycle(path, currentPos + 1) == 1)
                return 1;

            path[currentPos] = -1;
        }
        
        current = current->next;
    }
    

    return 0;
}

int8_t checkPathArray(int pos, int v, int *path)
{
    int i;

    for(i = 0; i < pos; i++)
        if(path[i] == v)
            return 0;

    return 1;
}

void printPath(int *path)
{
    int i;

    printf("%d ", path[0]);

    for (i = 1; i < AdjacencyListCount; i++)
        printf("-> %d ", path[i]);

    printf("\n");
}





void randomGraph(int n, float sat)
{
    //initAList(n);

    char buffer[255];
    int i, prob;

    float random = (float)rand()/RAND_MAX;
    if (random < prob) {
        addALEdge(i, prob);
        addALEdge(prob, i);    
    }
    
}



int main()
{

    
    int i, jp, jn = 6, noReturns = 10, avgFrom = 5, k;
    float prob[] = {0.2, 0.3, 0.4, 0.6, 0.8, 0.95};

    int *ns;
    double *times[jn];
    ns = (int *)calloc(noReturns, sizeof(int));

    for (jp = 0; jp < jn; jp++)
    {
        times[jp] = (double *)calloc(noReturns, sizeof(double));

        printf("\nHC for p=%f\n", prob[jp]);
        for (i = 1; i <= noReturns; i++)
        {
            int n = 25 * i;
            ns[i - 1] = n;
            times[jp][i - 1] = 0;
            for(k = 0; k < avgFrom; k++)
            {
                int i, j;

                AdjacencyList = (ALI **)calloc(n, sizeof(ALI *));
                AdjacencyListCount = n;
                for (int z=0; z<n; z++) {
                    AdjacencyList[z] = 0;
                }
                randomGraph(n, prob[jp]);



                clock_t begin = clock();
                hamiltonianCycle();
                clock_t end = clock();

                times[jp][i - 1] += (double)(end - begin) / CLOCKS_PER_SEC * 1000;

                freeAdjacencyList();
            }
            
            times[jp][i - 1] /= avgFrom;

            printf("%d - %fms\n", n, times[jp][i - 1]);
        }
    }

}