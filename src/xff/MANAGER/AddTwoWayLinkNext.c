int AddTwoWayLinkNext(int *a, int *b)
{
    int *n;
    int t = a[1];

    b[0] = (int)a;
    b[1] = t;
    n = (int *)a[1];
    if (n != 0) {
        n[0] = (int)b;
    }
    a[1] = (int)b;
    return 1;
}
