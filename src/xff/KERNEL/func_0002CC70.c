extern unsigned char B_000E11D0[];
extern int B_000E19D0;
extern int B_000E19D4;

static void func_0002CC70(unsigned char *p)
{
    unsigned char **cur = (unsigned char **)(p + 0x60);
    unsigned char a;
    unsigned char b;
    int status;
    int last = B_000E19D4;

    a = *(*cur)++;
    b = *(*cur)++;
    status = p[0x68];
    if (last != status) {
        B_000E19D4 = status;
        B_000E11D0[B_000E19D0++] = status;
    }
    B_000E11D0[B_000E19D0++] = a;
    B_000E11D0[B_000E19D0++] = b;
}
