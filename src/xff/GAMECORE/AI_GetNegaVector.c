void AI_GetNegaVector(void *arg0, void *arg1)
{
    (*(float *)((char *)(arg0) + 0)) = (float) -(*(float *)((char *)(arg1) + 0));
    (*(float *)((char *)(arg0) + 4)) = (float) -(*(float *)((char *)(arg1) + 4));
    (*(float *)((char *)(arg0) + 8)) = (float) -(*(float *)((char *)(arg1) + 8));
    (*(float *)((char *)(arg0) + 0xC)) = (float) (*(float *)((char *)(arg1) + 0xC));
}
