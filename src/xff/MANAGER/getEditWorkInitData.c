char *getEditWorkInitData(char *p)
{
    if (p != 0) {
        return p + *(int *)(p + 0x8);
    }
    return 0;
}
