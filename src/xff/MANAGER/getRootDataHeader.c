char *getRootDataHeader(char *p)
{
    int o = *(int *)(p + 0x10);

    if (o != 0) {
        return p + o;
    }
    return 0;
}
