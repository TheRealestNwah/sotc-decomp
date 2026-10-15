extern unsigned char *GetGeometryPointerObject(void *);
extern char *GetLayoutClass(void *);

unsigned char *SCRGetGetGeometryPointerLegalParentObj(void *g)
{
    unsigned char *o = GetGeometryPointerObject(g);
    if (o != 0 && o[8] == 0xA) {
        char *l = GetLayoutClass(o);
        if (*(int *)(l + 0x124) != 0) {
            unsigned char *p = GetGeometryPointerObject(l + 0xC0);
            if (p[8] == 0xD || p[8] == 0x16)
                o = p;
        }
    }
    return o;
}
