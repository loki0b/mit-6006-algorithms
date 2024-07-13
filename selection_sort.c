#include <stdio.h>

void swap(int *ap, int *bp) {
    int num;

    num = *ap;
    *ap = *bp;
    *bp = num;
}

void selection_sort(int *iter, int n) { 
    for (int i = 0; i < n - 1; i++) {
        int *max = iter;
        for (int j = 1; j < n - i; j++) {
            if (iter[j] > *max) {
                max = &(iter[j]);
            }
        }
        swap(max, &(iter[n - i - 1]));
   }
}