float gluGetBrightness(void *arg0)
{
    return ((*(float *)((char *)(arg0) + 0)) * 0.299000002443790435791015625f) + ((*(float *)((char *)(arg0) + 4)) * 0.58699996769428253173828125f) + ((*(float *)((char *)(arg0) + 8)) * 0.11399999447166919708251953125f);
}
