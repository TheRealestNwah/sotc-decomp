/* 2 diffs: register choice for &pkt temp (a3 vs v0) at 0x1A0 */
#ifdef NONMATCHING
typedef unsigned long u64 __attribute__((mode(DI)));
typedef unsigned int u128 __attribute__((mode(TI)));
typedef union { u64 d; float f[2]; int i[2]; void *p[2]; } PKT;
typedef struct {
    u64 NLOOP:15; u64 EOP:1; u64 pad16:16; u64 id:14; u64 PRE:1; u64 PRIM:11; u64 FLG:2; u64 NREG:4;
    u64 REGS0:4; u64 REGS1:4; u64 REGS2:4; u64 REGS3:4; u64 REGS4:4; u64 REGS5:4; u64 REGS6:4; u64 REGS7:4;
    u64 REGS8:4; u64 REGS9:4; u64 REGS10:4; u64 REGS11:4; u64 REGS12:4; u64 REGS13:4; u64 REGS14:4; u64 REGS15:4;
} GifTag;
typedef struct { int unk0; int fontId; int flag; } TextState;
typedef struct { int unk0[4]; int w; int h; int adv; int f1C; } FontInfo;

extern TextState D_001359F0;
extern int D_00135AA0;
extern unsigned short RO_0013CD88[];
extern unsigned int iosGetFontIDWithEUC(int);
extern void iosGetFontInfo(void *, int);
extern void iosDlChainTailCurrent(void *);
extern void gsRegBegin(void);
extern void gsRegEnd(void);
extern void gsReg(int, u64);
extern void *iosGetPacketPtrPath1(void);
extern void iosSetPacketPtrPath1(void *);
extern void func_00014CD0(float *, unsigned char *, FontInfo *);
extern int func_00014F18(PKT **, float *, unsigned int (*)(int), int, int);

static void func_00015310(float *r, unsigned char *s, unsigned int (*fn)(int))
{
    FontInfo info;
    PKT *pkt;
    int n = 0;
    PKT *top;
    int c;
    int k;
    int q;

    iosGetFontInfo(&info, D_001359F0.fontId);
    if (r[6] < r[0]) {
        k = *s;
        while (k) {
            if ((signed char)k >= 0) {
                if (*s == 10) {
                    r[0] = r[2];
                    r[1] += (float)(info.h - info.f1C) * r[15];
                }
            } else {
                s++;
            }
            s++;
            k = *s;
        }
    }
    if (r[7] < r[1]) {
        return;
    }
    if (D_001359F0.flag) {
        func_00014CD0(r, s, &info);
    }
    iosDlChainTailCurrent(&D_00135AA0);
    gsRegBegin();
    {
        gsReg(1, (u64)(int)(r[8] * 255.0f) | (u64)(int)(r[9] * 255.0f) << 8 | (u64)(int)(r[10] * 255.0f) << 16 | (u64)(int)(r[11] * 128.0f) << 24 | 0x3F80000000000000ULL);
    }
    gsRegEnd();
    top = iosGetPacketPtrPath1();
    pkt = top + 4;
    while (*s) {
        if (*s < 0x20) {
            switch (*s) {
            case 9:
                goto space;
            case 10:
                r[0] = r[2];
                r[1] += (float)(info.h - info.f1C) * r[15];
                break;
            }
        } else if ((unsigned char)(*s - 0x20) < 0x60) {
            if (*s == 0x20) {
            space:
                r[0] += (float)((info.w * 2 - info.adv) >> 1) * r[15];
            } else {
                n += func_00014F18(&pkt, r, iosGetFontIDWithEUC, RO_0013CD88[*s], 1);
            }
        } else {
            n += func_00014F18(&pkt, r, fn, (s[1] << 8) | *s++, 0);
        }
        s++;
    }
    while ((unsigned int)pkt & 0xF) {
        pkt++->d = 0;
    }
    iosSetPacketPtrPath1(pkt);
    if (n > 0) {
        q = ((unsigned int)((char *)pkt - (char *)top) >> 4) - 1;
        pkt = top;
        ((u64 *)pkt)[0] = q | 0x60000000;
        pkt = (PKT *)((char *)top + 8);
        *(int *)pkt = 0x10000000;
        pkt = (PKT *)((char *)top + 12);
        *(int *)pkt = q | 0x50000000;
        pkt = (PKT *)((char *)top + 16);
        *(u128 *)pkt = 0;
        ((GifTag *)pkt)->FLG = 1;
        ((GifTag *)pkt)->PRE = 0;
        ((GifTag *)pkt)->EOP = 1;
        ((GifTag *)pkt)->NREG = 6;
        ((GifTag *)pkt)->NLOOP = n;
        ((GifTag *)pkt)->REGS0 = 0;
        ((GifTag *)pkt)->REGS1 = 6;
        ((GifTag *)pkt)->REGS2 = 2;
        ((GifTag *)pkt)->REGS3 = 4;
        ((GifTag *)pkt)->REGS4 = 2;
        ((GifTag *)pkt)->REGS5 = 4;
        iosDlChainTailCurrent(top);
    }
}
#endif
