char *getInterestDataHeader(char *p)
{
    int o = *(int *)(p + 0x20);

    if (o != 0) {
        return p + o;
    }
    return 0;
}
