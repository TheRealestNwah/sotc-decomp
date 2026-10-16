extern char *GetLayoutClass(void *);
extern int ClipCollisionDirectCallBackOneObj(void *, void *, void *, void *, int, int, int, int);
extern void *SCRGetFirstObj(void *);
extern char gcGlobalVar[];

/* Inline, so gcc defers its own copy until after the caller below. */
inline int nico_CheckThroughObject(void *a, char *o)
{
    char buf[0x50];
    if (o != 0) {
        void *t = *(void **)(o + 8);
        char *lc;
        if (t == 0) return 0;
        lc = GetLayoutClass(a);
        if (ClipCollisionDirectCallBackOneObj(buf, *(void **)(lc + 0x138), *(void **)(lc + 0x134), t, 0, 0, 0, 0) != 0) return 1;
    }
    return 0;
}

int nico_CheckPlayerThroughObject(char *o)
{
    void *p = SCRGetFirstObj(gcGlobalVar + 0x2B0);
    if (p == 0) return 0;
    return nico_CheckThroughObject(p, o);
}
