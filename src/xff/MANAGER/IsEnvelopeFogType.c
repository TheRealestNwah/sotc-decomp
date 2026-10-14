int IsEnvelopeFogType(char *p)
{
    if (*(int *)(p + 0x40) & 0x800) {
        return 1;
    }
    return 0;
}
