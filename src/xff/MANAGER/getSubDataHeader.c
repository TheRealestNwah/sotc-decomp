char *getSubDataHeader(char *p)
{
    int o = *(int *)(p + 0x18);

    if (o != 0) {
        return p + o;
    }
    return 0;
}
