char *getPointDataHeader(char *p)
{
    int o = *(int *)(p + 0x8);

    if (o != 0) {
        return p + o;
    }
    return 0;
}
