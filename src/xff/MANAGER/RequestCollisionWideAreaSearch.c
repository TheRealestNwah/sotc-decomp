extern void CopyGeometryPointer(void *, void *);

int RequestCollisionWideAreaSearch(char *s, void *a, void *b)
{
    *(int *)(s + 4) = 0;
    *(int *)(s + 0) = 0;
    CopyGeometryPointer(s + 0x20, a);
    CopyGeometryPointer(s + 0x60, b);
    return 0;
}
