extern unsigned long *GetCollisionDBAttributeAdr(void *);
extern void GetCollisionDBNext3Direct(int *, int *);
extern void MakeCollisionEdgePointer(char *, int *, int);

static int T_0005C0C0(char *a, int *b)
{
    int cnt = 0;
    int max;
    char *out;
    int n;
    int *p;
    int nb[6];
    int *q;
    int i;
    int k;

    max = *(short *)(a + 0x10);
    p = (int *)b[3];
    n = b[1] < b[0] ? b[1] : b[0];
    out = *(char **)(a + 0x24);
    for (n--; n != -1; n--, p += 2) {
        if (*p == 0)
            continue;
        if ((*GetCollisionDBAttributeAdr(p) & 0xF80000000) != 0x780000000)
            continue;
        GetCollisionDBNext3Direct(nb, p);
        for (i = 0, q = nb, k = 2; k != -1; k--, q += 2, i++) {
            if (*q == 0)
                continue;
            if ((*GetCollisionDBAttributeAdr(q) & 0xF80000000) == 0x780000000)
                continue;
            MakeCollisionEdgePointer(out, p, i);
            out += 0x14;
            if (++cnt >= max)
                goto end;
        }
    }
end:
    return cnt;
}
