#ifdef NONMATCHING
/* 42 diffs: out pinned to s5 and the inner index to s4 like the Original, and the inner skip test reads attr & 4 first. Remaining: the Original loads out before max in the prologue, computes both attr masks before testing ==1 with a beql/bnel pair (ours bnez/beq), and puts i++ rather than p += 2 in the inner loop's branch delay slot. Permuter 915 -> 710 in ~20 min on the earlier form. */
extern unsigned long *GetCollisionDBAttributeAdr(void *surface);
extern void GetCollisionDBNext3Direct(void *out, void *surface);
extern void MakeCollisionEdgePointer(void *out, void *surface, int index);

static int func_0007C828(char *obj, int *db)
{
    int count = 0;
    int nb = db[1];
    int n = db[0];
    register char *out __asm__("$21") = *(char **)(obj + 0x24);
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
        register int i __asm__("$20");
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
            if ((attr & 4) != 0 || (attr & 3) == 1)
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
