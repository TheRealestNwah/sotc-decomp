extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;

static void func_00024C58(void)
{
    unsigned short v[2];
    unsigned int mode = B_000C5C0C[2];
    int ch = B_000C5C0C[0] & 0xF;

    if (mode >= 4) {
        v[1] = -1;
        v[0] = -1;
    } else if (mode == 2) {
        v[0] = 1;
        v[1] = -1;
    } else if (mode == 1) {
        v[1] = 1;
        v[0] = -1;
    } else {
        v[1] = 1;
        v[0] = 1;
    }
    {
        register char *base __asm__("$3") = B_000C5C10;
        register int off __asm__("$2") = ch * 0x70;
        register char *q __asm__("$4") = (char *)(off + (int)base);
        __asm__("" : "+r"(q));
        *(unsigned short *)(q + 0x2F4) = v[0];
        {
            register char *g __asm__("$2") = q;
            __asm__ volatile ("" : "+r"(g));
            *(unsigned short *)(g + 0x2F6) = v[1];
        }
    }
}
