extern void PutStringS(int attr, const char *format, ...);
extern int padSysReadForLoader(void);
extern void Sync(void);
extern void ExecBaseProc(void);
extern char D_0013A0E8[];
extern char D_001371B0[];
extern char D_001371C8[];
extern char D_001371E0[];
extern char D_00137208[];
extern char D_00137230[];
extern char D_00137240[];

int func_00104818(void) {
    int i = 0;
    int pad;

    PutStringS(0x80C0FF00, D_0013A0E8);
    pad = 0;
    while (i++ < 30) {
        pad = padSysReadForLoader();
        if (pad != 0) {
            break;
        }
        Sync();
        ExecBaseProc();
    }
    switch (pad) {
    case 0x800:
        pad = 3;
        PutStringS(0x80C0FF00, D_001371B0);
        break;
    case 0x20:
        pad = 1;
        PutStringS(0x80C0FF00, D_001371C8);
        break;
    case 0x10:
        pad = 2;
        PutStringS(0x80C0FF00, D_001371E0);
        break;
    case 0x80:
        pad = 4;
        PutStringS(0x80C0FF00, D_00137208);
        break;
    case 0x40:
        pad = 5;
        PutStringS(0x80C0FF00, D_00137230);
        break;
    default:
        pad = 0;
        PutStringS(0x80C0FF00, D_00137240);
        break;
    }
    return pad;
}
