extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;

/* Parked: 6 diffs: the final channel pointer is copied to a second register before the second halfword store */
#ifdef NONMATCHING
static void func_00024C58(void)
{
    unsigned short v[2];
    unsigned int mode = B_000C5C0C[2];
    int ch = B_000C5C0C[0] & 0xF;
    char *p;

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
    p = B_000C5C10 + ch * 0x70;
    *(unsigned short *)(p + 0x2F4) = v[0];
    *(unsigned short *)(p + 0x2F6) = v[1];
}
#else
extern void func_00024C58(void);
#endif
