float GetYHeightOfPlaneXZProjection(void *arg0, void *arg1)
{
    return -(((*(float *)((char *)(arg0) + 0)) * (*(float *)((char *)(arg1) + 0))) + ((*(float *)((char *)(arg0) + 8)) * (*(float *)((char *)(arg1) + 8))) + (*(float *)((char *)(arg0) + 0xC))) / (*(float *)((char *)(arg0) + 4));
}
