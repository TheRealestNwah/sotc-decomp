extern void *GetLayoutClass(void *);
extern void *GetLayoutParentObj(void *);
void *GAMEUTIL_get_parent_object(void *actor)
{
    void *l = GetLayoutClass(actor);
    if (l == 0)
        return 0;
    return GetLayoutParentObj(l);
}
