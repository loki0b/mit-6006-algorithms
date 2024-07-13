#include <stdio.h>

// return the index of the k element if exists, if not return -1
int binary_search(int *iter, int k, int n) {
    int m, l, r;

    l = 0;
    r = n;
    while (l < r) {
        m = (l + r) / 2;
        if (k == iter[m]) { return m; }
        else if (k < iter[m]) { r = m - 1; }
        else { l = m + 1; }
    }

    return -1;
}