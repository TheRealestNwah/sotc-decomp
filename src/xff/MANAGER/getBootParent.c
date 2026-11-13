extern void *GetGeometryPointerObject(void *);
extern char *GetLayoutClass(void *);

void *getBootParent(void *g)
{
    void *parent = 0;
    void *obj = GetGeometryPointerObject(g);
    char *lc;

    while (obj != 0) {
        lc = GetLayoutClass(obj);
        if (lc == 0)
            break;
        parent = obj;
        if (*(int *)(lc + 0x124) == 0)
            break;
        obj = GetGeometryPointerObject(lc + 0xC0);
    }
    return parent;
}
