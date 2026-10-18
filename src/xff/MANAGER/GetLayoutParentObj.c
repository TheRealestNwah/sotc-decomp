extern void *GetGeometryPointerObject(char *);

int GetLayoutParentObj(void *arg0)
{
    if ((*(int *)((char *)(arg0) + 0x124)) != 0) {
        return (int)GetGeometryPointerObject((char *)arg0 + 0xC0);
    }
    return 0;
}
