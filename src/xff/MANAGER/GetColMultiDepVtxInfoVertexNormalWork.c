void GetColMultiDepVtxInfoVertexNormalWork(void *arg0, void *arg1, void *arg2)
{
    int temp_a2;

    temp_a2 = (*(int *)((char *)(arg2) + 0));
    (*(int *)((char *)(arg0) + 0)) = (int) (*(int *)((char *)(arg2) + 4));
    if (temp_a2 != -1) {
        (*(void **)((char *)(arg0) + 4)) = (void *) ((*(int *)((char *)((*(void **)((char *)(arg1) + 0x174))) + 0x24)) + (temp_a2 * 0x60) + 0x18);
        return;
    }
    (*(void **)((char *)(arg0) + 4)) = (void *) ((*(void **)((char *)(arg1) + 0x174)) + 0x40);
}
