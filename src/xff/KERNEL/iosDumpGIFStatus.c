typedef unsigned int u32;
typedef struct { char *s[2]; } Str2;
typedef struct { char *s[4]; } Str4;

extern void LoaderSysPrintf(const char *fmt, ...);
extern Str2 RO_00043718, RO_00043740, RO_00043760, RO_00043768, RO_00043780, RO_000437C0;
extern Str4 RO_000437A0, RO_00043808;
extern char RO_00043818[], RO_00043850[], RO_00043868[], RO_00043880[], RO_00043898[], RO_000438B0[],
    RO_000438C8[], RO_000438E0[], RO_000438F8[], RO_00043910[], RO_00043928[], RO_00043940[], RO_00043958[],
    RO_00043508[], RO_00043978[], RO_00043998[], RO_000439D8[], RO_00043A20[];

#define R(a) (*(volatile u32 *)(a))

#ifdef NONMATCHING
/* Parked: 149 words differ. Register allocation and frame match; gcc hoists the
   GIF_STAT load and field shifts into the table copies, which the Original keeps in order. */
void iosDumpGIFStatus(void)
{
    Str2 t0, t1, t2, t3, t4;
    Str4 t5;
    Str2 t6;
    Str4 t7;
    volatile u32 *stp = (volatile u32 *)0x10003020;
    u32 stat;
    u32 m3r, m3p, imt, pse, ip3, p3q, p2q, p1q, oph, apath, dir, fqc;

    t0 = RO_00043718;
    t1 = RO_00043740;
    t2 = RO_00043760;
    t3 = RO_00043768;
    t4 = RO_00043780;
    t5 = RO_000437A0;
    t6 = RO_000437C0;
    t7 = RO_00043808;
    stat = *stp;
    LoaderSysPrintf(RO_00043818);
    m3r = stat & 1;
    m3p = (stat >> 1) & 1;
    imt = (stat >> 2) & 1;
    pse = (stat >> 3) & 1;
    ip3 = (stat >> 5) & 1;
    p3q = (stat >> 6) & 1;
    p2q = (stat >> 7) & 1;
    p1q = (stat >> 8) & 1;
    oph = (stat >> 9) & 1;
    apath = (stat >> 10) & 3;
    dir = (stat >> 12) & 1;
    fqc = (stat >> 24) & 0x1F;
    LoaderSysPrintf(RO_00043850, t0.s[m3r], apath, fqc);
    LoaderSysPrintf(RO_00043868, t0.s[m3p]);
    LoaderSysPrintf(RO_00043880, t1.s[imt]);
    LoaderSysPrintf(RO_00043898, t2.s[pse]);
    LoaderSysPrintf(RO_000438B0, t3.s[ip3]);
    LoaderSysPrintf(RO_000438C8, t3.s[p3q]);
    LoaderSysPrintf(RO_000438E0, t3.s[p2q]);
    LoaderSysPrintf(RO_000438F8, t3.s[p1q]);
    LoaderSysPrintf(RO_00043910, t4.s[oph]);
    LoaderSysPrintf(RO_00043928, t5.s[apath]);
    LoaderSysPrintf(RO_00043940, t6.s[dir]);
    LoaderSysPrintf(RO_00043958, fqc, fqc);
    LoaderSysPrintf(RO_00043508);
    LoaderSysPrintf(RO_00043978, R(0x10003070), R(0x10003060));
    LoaderSysPrintf(RO_00043998, R(0x10003040) & 0x7FFF, R(0x10003040) & 0x7FFF, (R(0x10003040) >> 15) & 1,
                    (R(0x10003050) >> 14) & 1, (R(0x10003050) >> 15) & 0x7FF, t7.s[(R(0x10003050) >> 26) & 3],
                    R(0x10003050) >> 28);
    LoaderSysPrintf(RO_000439D8, R(0x10003080) & 0x7FFF, (R(0x10003080) >> 16) & 0xF, (R(0x10003080) >> 20) & 0x3FF);
    LoaderSysPrintf(RO_00043A20, *stp);
}
#endif
