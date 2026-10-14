char *getDeadDataHeader(char *p)
{
    int o = *(int *)(p + 0x24);

    if (o != 0) {
        return p + o;
    }
    return 0;
}
