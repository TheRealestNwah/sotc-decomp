void iosGetScaleInverseVector(void *arg0, void *arg1)
{
    (*(float *)((char *)(arg0) + 0)) = (float) (1.0f / (*(float *)((char *)(arg1) + 0)));
    (*(float *)((char *)(arg0) + 4)) = (float) (1.0f / (*(float *)((char *)(arg1) + 4)));
    (*(float *)((char *)(arg0) + 8)) = (float) (1.0f / (*(float *)((char *)(arg1) + 8)));
    (*(float *)((char *)(arg0) + 0xC)) = (float) (1.0f / (*(float *)((char *)(arg1) + 0xC)));
}
