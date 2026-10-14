char *getLineDataHeader(char *p)
{
    int o = *(int *)(p + 0xC);

    if (o != 0) {
        return p + o;
    }
    return 0;
}
