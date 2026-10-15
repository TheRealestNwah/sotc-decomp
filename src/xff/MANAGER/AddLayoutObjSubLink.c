extern char *GetLayoutClass(void *);
extern void *GetSubLinkClass(void *);
extern void AddTwoWayLinkNext(void *, void *);

void AddLayoutObjSubLink(void *a, void *b)
{
    char *l = GetLayoutClass(a);
    void *s = GetSubLinkClass(b);
    AddTwoWayLinkNext(l + 0x10C, s);
}
