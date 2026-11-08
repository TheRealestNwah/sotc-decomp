#ifdef NONMATCHING
/* 46 diffs: register allocation (outer/inner counters swapped) and load scheduling; permuter 915 -> 710 in ~20 min. */
extern unsigned long *GetCollisionDBAttributeAdr(void *surface);
extern void GetCollisionDBNext3Direct(void *out, void *surface);
extern void MakeCollisionEdgePointer(void *out, void *surface, int index);

static int func_0007C828(char *obj, int *db)
{
    int count = 0;
    int nb = db[1];
    int n = db[0];
    char *out = *(char **)(obj + 0x24);
    int max = *(short *)(obj + 0x10);
    int *item;
    int next[6];

    if (nb < n)
        n = nb;
    n--;
    item = (int *)db[3];
    for (; n != -1; n--, item += 2) {
        unsigned long attr;
        int *p;
        int i;
        int k;

        if (item[0] == 0)
            continue;
        attr = *GetCollisionDBAttributeAdr(item);
        if ((attr & 3) != 1 && (attr & 4) == 0)
            continue;
        GetCollisionDBNext3Direct(next, item);
        p = next;
        for (i = 0, k = 2; k != -1; k--, i++, p += 2) {
            if (p[0] == 0)
                continue;
            attr = *GetCollisionDBAttributeAdr(p);
            if ((attr & 3) == 1 || (attr & 4) != 0)
                continue;
            MakeCollisionEdgePointer(out, item, i);
            out += 0x14;
            count++;
            if (count >= max)
                return count;
        }
    }
    return count;
}
#endif
