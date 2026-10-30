extern void func_00095C08(void *, void *, float);

static void func_000989D0(char *p)
{
    char *s = 0;
    int i;

    if (*(unsigned char *)(p + 8) == 0x21)
        s = p + 0x90;
    for (i = 0; i < *(int *)(s + 8); i++) {
        char *item = *(char **)(s + 4) + i * 0x44;
        if (*(int *)(item + 8) & 0xF)
            func_00095C08(p, item, 1.0f);
    }
}
