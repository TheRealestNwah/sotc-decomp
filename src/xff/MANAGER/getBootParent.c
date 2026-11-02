#ifdef NONMATCHING
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
