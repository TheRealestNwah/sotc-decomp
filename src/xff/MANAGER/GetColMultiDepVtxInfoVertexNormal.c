int GetColMultiDepVtxInfoVertexNormal(void *arg0, void *arg1)
{
    int temp_a1;
    int temp_v1;

    temp_v1 = (*(int *)((char *)(arg1) + 0));
    temp_a1 = (*(int *)((char *)(arg1) + 4));
    if (temp_v1 != -1) {
        return (*(int *)((char *)(((temp_v1 * 0x60) + (*(int *)((char *)((*(void **)((char *)(arg0) + 0x174))) + 0x24)))) + 0x2C)) + (temp_a1 * 0x10);
    }
    return (*(int *)((char *)((*(void **)((char *)(arg0) + 0x174))) + 0x54)) + (temp_a1 * 0x10);
}
