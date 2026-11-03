static void func_00061D40(int *rank, int n, int m, float *val)
{
    int i, j, k, tmp, t;
    float max;

    for (k = 0; k < n; k++)
        rank[k] = 0;
    max = val[k];
    for (k = 0; k < m; k++) {
        if (max < val[k]) {
            rank[0] = k;
            max = val[k];
        }
    }
    i = 0;
    for (j = 0; j < m; j++) {
        for (; i < n; i++) {
            if (*(volatile float *)&val[j] <= val[rank[i]] && rank[i] != j) {
                tmp = rank[i];
                rank[i] = j;
                for (i++; i < n; i++) {
                    t = rank[i];
                    rank[i] = tmp;
                    tmp = t;
                }
            }
        }
        i = 0;
    }
}
