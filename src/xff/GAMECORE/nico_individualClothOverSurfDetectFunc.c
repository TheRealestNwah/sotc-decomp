extern int CheckUnderVariableXZSurface(void *, void *, void *, void *);

int nico_individualClothOverSurfDetectFunc(char *p, void *pos)
{
    char buf[0x50];
    void *s = *(void **)(*(char **)(p + 0xC) + 0x10);

    return CheckUnderVariableXZSurface(buf, s, s, pos) == 0;
}
