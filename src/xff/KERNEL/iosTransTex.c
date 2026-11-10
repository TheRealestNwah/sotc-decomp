typedef unsigned long u64;
typedef unsigned int u32;
typedef int s128 __attribute__((mode(TI)));

typedef struct {
    u64 NLOOP : 15;
    u64 EOP : 1;
    u64 pad16 : 16;
    u64 id : 14;
    u64 PRE : 1;
    u64 PRIM : 11;
    u64 FLG : 2;
    u64 NREG : 4;
    u64 REGS0 : 4;
    u64 REGS1 : 4;
    u64 REGS2 : 4;
    u64 REGS3 : 4;
    u64 REGS4 : 4;
    u64 REGS5 : 4;
    u64 REGS6 : 4;
    u64 REGS7 : 4;
    u64 REGS8 : 4;
    u64 REGS9 : 4;
    u64 REGS10 : 4;
    u64 REGS11 : 4;
    u64 REGS12 : 4;
    u64 REGS13 : 4;
    u64 REGS14 : 4;
    u64 REGS15 : 4;
} GifTagB;

typedef union {
    s128 q;
    GifTagB b;
} GifTag;

typedef struct {
    u64 w[6];
} Tail48;

extern Tail48 D_00040C00;
extern u64 *iosGetPacketPtrPath1(void);
extern void iosSetPacketPtrPath1(u64 *);
extern void iosDlChainTailCurrent(void *);

#ifdef NONMATCHING
/* Parked: same packet, but the original keeps the packet pointer in two
   registers (t1 and s0), which shifts the register allocation. */
void iosTransTex(void *src, int dbp, int w, int h, int psm)
{
    u64 *p;
    char *q;
    int qwc;

    q = (char *)iosGetPacketPtrPath1();
    p = (u64 *)q;
    if (q == 0) {
        return;
    }
    ((GifTag *)&p[2])->q = 0;
    ((GifTag *)&p[2])->b.EOP = 1;
    ((GifTag *)&p[2])->b.NREG = 1;
    ((GifTag *)&p[2])->b.NLOOP = 4;
    ((GifTag *)&p[2])->b.REGS0 = 0xE;
    p[4] = ((u64)dbp << 32) | ((u64)(w >> 6) << 48) | ((u64)psm << 56);
    p[5] = 0x50;
    p[6] = 0;
    p[7] = 0x51;
    p[8] = (u64)w | ((u64)h << 32);
    p[9] = 0x52;
    p[10] = 0;
    p[11] = 0x53;
    p[0] = (((GifTag *)&p[2])->b.NLOOP + 1) | 0x10000000;
    ((int *)p)[2] = 0;
    ((int *)p)[3] = ((int)((GifTag *)&p[2])->b.NLOOP + 1) | 0x50000000;
    q += 0x60;

    switch (psm) {
    case 0:
        qwc = w * h * 4;
        break;
    case 1:
        qwc = w * h * 3;
        break;
    case 2:
    case 10:
        qwc = w * h * 2;
        break;
    case 0x13:
    case 0x1B:
        qwc = w * h;
        break;
    case 0x14:
    case 0x24:
    case 0x2C:
        qwc = (w * h) >> 1;
        break;
    default:
        qwc = -1;
        break;
    }
    qwc >>= 4;

    *(u64 *)q = 0x10000001;
    q += 8;
    *(u32 *)q = 0x11000000;
    q += 4;
    *(u32 *)q = 0x50000001;
    q += 4;
    *(u64 *)q = (u64)qwc | 0x8000 | ((u64)2 << 58);
    q += 8;
    *(u64 *)q = 0;
    q += 8;
    *(u64 *)q = (qwc | 0x30000000) | ((u64)(u32)src << 32);
    q += 8;
    *(u32 *)q = 0;
    q += 4;
    *(u32 *)q = qwc | 0x50000000;
    q += 4;
    *(Tail48 *)q = D_00040C00;
    iosSetPacketPtrPath1((u64 *)(q + 0x30));
    iosDlChainTailCurrent(p);
}
#endif
