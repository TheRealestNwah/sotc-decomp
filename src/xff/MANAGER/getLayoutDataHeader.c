char *getLayoutDataHeader(char *p)
{
    int o = *(int *)(p + 0x28);

    if (o != 0) {
        return p + o;
    }
    return 0;
}
