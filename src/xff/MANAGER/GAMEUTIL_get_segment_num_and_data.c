extern int DldSysUndefSymbol;
static inline int dldCount(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? t[3] : 0;
}
static inline int *dldObj(int *h)
{
    int off = *h & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return (t != 0 && t != (int *)DldSysUndefSymbol) ? (int *)t[4] : 0;
}
void *GAMEUTIL_get_segment_num_and_data(int *count, int *handle)
{
    if (count) *count = dldCount(handle);
    return dldObj(handle);
}
