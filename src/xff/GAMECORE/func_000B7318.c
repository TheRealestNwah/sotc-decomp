extern void func_000B5318(void *);

static void func_000B7318(char *a)
{
    int i;
    char *p = a + 0x250;

    for (i = 0x13; i >= 0; i--) {
        func_000B5318(p);
        p += 0x60;
    }
}
