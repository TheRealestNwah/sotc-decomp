extern int GetGeometryPointerObject(void *);

int GetLayoutParentObj(void *arg0)
{
    if ((*(int *)((char *)(arg0) + 0x124)) != 0) {
        return GetGeometryPointerObject(arg0 + 0xC0);
    }
    return 0;
}
