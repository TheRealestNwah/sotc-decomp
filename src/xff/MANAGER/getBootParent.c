#ifdef NONMATCHING /* 6 diffs: the original returns 0 through a beql on obj == 0 and fills the jal delay slot with daddu a0,s0. Permuter (25 min) found only semantics-changing variants. */
extern void *GetGeometryPointerObject(void *);
extern char *GetLayoutClass(void *);

void *getBootParent(void *g)
{
    void *parent = 0;
    void *obj;

    while ((obj = GetGeometryPointerObject(g)) != 0) {
        char *lc = GetLayoutClass(obj);
        if (lc == 0)
            break;
        g = lc + 0xC0;
        parent = obj;
        if (*(int *)(lc + 0x124) == 0)
            break;
    }
    return parent;
}
#endif
