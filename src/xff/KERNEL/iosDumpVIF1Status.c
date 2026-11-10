typedef unsigned int u32;
typedef struct { char *s[2]; } Str2;
typedef struct { char *s[4]; } Str4;

extern void LoaderSysPrintf(const char *fmt, ...);
extern Str2 RO_000432F8, RO_00043370, RO_00043398, RO_000433C0;
extern Str4 RO_00043340;
extern char RO_000432B0[], RO_000433C8[], RO_000433E0[], RO_000433F8[], RO_00043410[], RO_00043428[],
    RO_00043440[], RO_00043458[], RO_00043470[], RO_00043488[], RO_000434A0[], RO_000434B8[], RO_000434D0[],
    RO_000434E8[], RO_00043508[], RO_00043528[], RO_00043540[], RO_000435A0[], RO_00043600[], RO_00043648[],
    RO_000436A8[];

#define R(a) (*(volatile u32 *)(a))

#ifdef NONMATCHING
/* Parked: copy order of the local string tables and register choice differ. */
void iosDumpVIF1Status(void)
{
    Str2 yn;
    Str4 vps;
    Str2 a, b, c;
    u32 stat;
    int fqc;

    LoaderSysPrintf(RO_000432B0);
    stat = R(0x10003C00);
    yn = RO_000432F8;
    vps = RO_00043340;
    a = RO_00043370;
    b = RO_00043398;
    c = RO_000433C0;
    LoaderSysPrintf(RO_000433C8, vps.s[stat & 3]);
    LoaderSysPrintf(RO_000433E0, a.s[(stat >> 2) & 1]);
    LoaderSysPrintf(RO_000433F8, b.s[(stat >> 3) & 1]);
    LoaderSysPrintf(RO_00043410, yn.s[(stat >> 6) & 1]);
    LoaderSysPrintf(RO_00043428, (stat >> 7) & 1);
    LoaderSysPrintf(RO_00043440, yn.s[(stat >> 8) & 1]);
    LoaderSysPrintf(RO_00043458, yn.s[(stat >> 9) & 1]);
    LoaderSysPrintf(RO_00043470, yn.s[(stat >> 10) & 1]);
    LoaderSysPrintf(RO_00043488, yn.s[(stat >> 11) & 1]);
    LoaderSysPrintf(RO_000434A0, yn.s[(stat >> 12) & 1]);
    LoaderSysPrintf(RO_000434B8, yn.s[(stat >> 13) & 1]);
    fqc = (stat >> 24) & 0x1F;
    LoaderSysPrintf(RO_000434D0, c.s[(stat >> 23) & 1]);
    LoaderSysPrintf(RO_000434E8, fqc, fqc);
    LoaderSysPrintf(RO_00043508);
    LoaderSysPrintf(RO_00043528, R(0x10003C30));
    LoaderSysPrintf(RO_00043540, R(0x10003D00), R(0x10003D10), R(0x10003D20), R(0x10003D30));
    LoaderSysPrintf(RO_000435A0, R(0x10003D40), R(0x10003D50), R(0x10003D60), R(0x10003D70));
    LoaderSysPrintf(RO_00043600, R(0x10003C40), R(0x10003C70), R(0x10003C50));
    LoaderSysPrintf(RO_00043648, R(0x10003CD0), R(0x10003C90), R(0x10003CA0), R(0x10003CB0));
    LoaderSysPrintf(RO_000436A8, R(0x10003CE0), R(0x10003CC0), R(0x10003C60), R(0x10003C80));
}
#endif
