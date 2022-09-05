#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick.h"
#include "merge.h"
#include "heap.h"

int main() {
    int n;
    printf("\nSorting : Quick, Heap, Merge\n\n");
    
    static int toSort1[100000000];
    static int toSort2[100000000];
    static int toSort3[100000000];

    int i, num;
    n = 10000;
    int itter = 0;

    

    while (itter<15) {

        int a;
        a = n-1;
        //a = 0;

        for (i = 0; i<n; i++) {
            num = rand() % 100;
            // a--;
            // num = a;
            // a++;
            // if (i<(n/2)-1) {
            //     num = a;
            //     a = a - 2;
            // }
            // else if (i >= (n/2)) {
            //     num = a;
            //     a = a+2;
            // }
            // else {
            //     num = a;
            //     a = a - 1;
            // }

            
            
            toSort1[i] = num;
            toSort2[i] = num;
            toSort3[i] = num;
            //printf(" %d", num);
        }
        printf("%d\n", n);

        clock_t start = clock();
        QuickSort(toSort1, 0, n-1);
        clock_t end = clock();
        double t;
        t = (end-start)*1000/CLOCKS_PER_SEC;
        printf("%f  ", t);

        clock_t start2 = clock();
        HeapSort(toSort2, n);
        clock_t end2 = clock();
        double t2;
        t2 = (end2-start2)*1000/CLOCKS_PER_SEC;
        printf("%f  ", t2);

        clock_t start3 = clock();
        MergeSort(toSort3, 0, n-1);
        clock_t end3 = clock();
        double t3;
        t3 = (end3-start3)*1000/CLOCKS_PER_SEC;
        printf("%f  \n\n", t3);


        n += 10000;
        itter++;
    }

    return 0;
}