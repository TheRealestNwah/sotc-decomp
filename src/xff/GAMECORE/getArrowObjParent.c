extern char *B_00189DF4;
extern char *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(void *);

int getArrowObjParent(void *parent)
{
    char *p = B_00189DF4;
    int n = 0;

    while (p != 0) {
        char *next = *(char **)(p + 0xC0);
        char *c = GetLayoutClass(*(void **)(p + 0x94));

        if (*(int *)(c + 0x124) != 0 && parent == GetGeometryPointerObject(c + 0xC0)) {
            short t = *(short *)(p + 0xA0);

            if (t == 2 || t == 5)
                n++;
        }
        p = next;
    }
    return n;
}
