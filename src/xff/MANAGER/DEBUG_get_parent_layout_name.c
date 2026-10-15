extern void *GetLayoutClass(void *);
extern void *GetLayoutParentObj(void *);

char *DEBUG_get_parent_layout_name(void *actor, char *def)
{
    void *p = GetLayoutParentObj(GetLayoutClass(actor));
    if (p == 0)
        return def;
    return *(char **)((char *)GetLayoutClass(p) + 0x130);
}
