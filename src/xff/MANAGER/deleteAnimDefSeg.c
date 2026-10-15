extern void isysRequestDeleteObj(void *);

void deleteAnimDefSeg(char *s)
{
    int i = *(int *)(s + 0xC);
    char *p = *(char **)(s + 0x10);
    while (--i != -1) {
        if (*(void **)(p + 0x6C) != 0) {
            isysRequestDeleteObj(*(void **)(p + 0x6C));
            *(void **)(p + 0x6C) = 0;
        }
        p += 0x74;
    }
}
