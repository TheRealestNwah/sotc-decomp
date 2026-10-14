char *getEditWorkDebugHeader(char *p)
{
    int o;

    if (p == 0) {
        goto no;
    }
    o = *(int *)(p + 0xC);
    if (o == 0) {
        goto no;
    }
    return p + o;
no:
    return 0;
}
