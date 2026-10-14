int useTempAttain(char *p)
{
    if (*(int *)(p + 0x3A0) != 0) {
        goto no;
    }
    if (*(int *)(p + 0x410) == 0) {
        goto no;
    }
    return 1;
no:
    return 0;
}
