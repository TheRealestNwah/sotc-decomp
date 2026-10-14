int GetGeometryPointerObjectParentNodeId(char *p)
{
    if (*(int *)(p + 0x30) != 1) {
        return -1;
    }
    return *(int *)(p + 0x4);
}
