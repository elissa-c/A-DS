#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "create_graph.h"
#define V 20

void printSolution(int path[]);

bool isSafe(int v, int graph[V][V], int path[], int pos)
{
    
    if (graph [ path[pos-1] ][ v ] == 0)
        return false;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}
bool hamCycleUtil(int graph[V][V], int path[], int pos)
{
    if (pos == V)
    {
        if ( graph[ path[pos-1] ][ path[0] ] == 1 )
           return true;
        else
          return false;
    }

    for (int v = 1; v < V; v++)
    {
        if (isSafe(v, graph, path, pos))
        {
            path[pos] = v;

            if (hamCycleUtil (graph, path, pos+1) == true)
                return true;

            path[pos] = -1;
        }
    }
        return false;
}

bool hamCycle(int graph[V][V])
{
    //int V;
    int *path;
    for (int i = 0; i < V; i++)
        path[i] = -1;

    path[0] = 0;
    if ( hamCycleUtil(graph, path, 1) == false )
    {
        printf("\nSolution does not exist");
        return false;
    }

    printSolution(path);
    return true;
}

void printSolution(int path[])
{
    printf ("Solution Exists:"
            " Following is one Hamiltonian Cycle \n");
    for (int i = 0; i < V; i++)
        printf(" %d ", path[i]);

    printf(" %d ", path[0]);
    printf("\n");
}


int main() {
    int itter = 0;
    float t=0;
    int noReturns = 1;

    while (itter<noReturns) {
        clock_t start = clock();
        create_undirected(mat);
        printf("%d\n", mat[2][2]);
        
        bool status = hamCycle(mat);

        clock_t end = clock();
        if (status == true){
            t += (end-start);
            itter++;
        }
    }
    printf("%d %f\n", size, t/noReturns);

    return 0;
}
