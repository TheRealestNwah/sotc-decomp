extern char gcGlobalVar[];
extern char *GetLayoutClass(void *);
extern void *SCRGetFirstObj(void *);
extern void *GetGeometryPointerObject(char *);

int AI_CheckHorseParent(void *o)
{
    char *l = GetLayoutClass(o);
    void *h = SCRGetFirstObj(gcGlobalVar + 0x2B4);
    if (h == 0)
        return 0;
    return GetGeometryPointerObject(l + 0xC0) == h;
}
