extern unsigned char *B_000C5C0C;
extern char *B_000C5C10;
extern void Sg2SlotSetDumperOff(int vab, int prog);

static void func_00024A00(void)
{
    unsigned char *ev = B_000C5C0C;
    int ch = ev[0] & 0xF;
    char *st;

    if (ev[2] < 0x7E) {
        st = B_000C5C10;
        *(int *)(st + ch * 0x70 + 0x2E0) = 0;
        Sg2SlotSetDumperOff(*(int *)(st + 4), ch);
    } else {
        *(int *)(B_000C5C10 + ch * 0x70 + 0x2E0) = 1;
    }
}
