/* Parked attempt: 227 diffs (try_compilers -O2 -G0, --asm-fill-delay-slots from config/ee_cflags.json). */
#ifdef NONMATCHING
typedef struct {
    int f00;
    int f04;
    int f08;
    int f0C;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    int f24;
    int f28;
    int f2C;
    int f30;
    int f34;
    int f38;
    int f3C;
    int f40;
    int f44;
    int f48;
    int f4C;
    int f50;
    int f54;
    int f58;
    int f5C;
    int f60;
    int f64;
    int f68;
    int f6C;
    int f70;
    short f74;
    short f76;
    int f78;
    int f7C;
    int f80;
    void * f84;
    void * f88;
    void * f8C;
    int f90;
    int f94;
    int f98;
    void * f9C;
    void * fA0;
    void * fA4;
    int fA8;
    int fAC;
    float fB0;
    int fB4;
    int fB8;
    float fBC;
    int fC0;
    int fC4;
    float fC8;
    int fCC;
    int fD0;
    int fD4;
    float fD8;
    float fDC;
} Slot;

extern Slot B_000DE370[];
extern unsigned int B_000DE360;
extern char D_000414A0[];
extern char D_000414DC[];
extern int DIntr(void);
extern int EIntr(void);

/* Slot reset shared with Sg2SlotInit's loop body (same store sequence). */
#define SG2_SLOT_CLEAR(i_, z_) \
        B_000DE370[i_].f00 = 0; \
        B_000DE370[i_].f04 = B_000DE370[i_].f08 = 0; \
        B_000DE370[i_].f20 = 0; \
        B_000DE370[i_].f18 = B_000DE370[i_].f1C = -1; \
        B_000DE370[i_].f38 = B_000DE370[i_].f3C = 127; \
        B_000DE370[i_].f40 = B_000DE370[i_].f44 = 127; \
        B_000DE370[i_].f4C = B_000DE370[i_].f50 = 0x40; \
        B_000DE370[i_].f48 = B_000DE370[i_].f54 = -1; \
        B_000DE370[i_].f34 = B_000DE370[i_].f70 = 0x1000; \
        B_000DE370[i_].f30 = 0; \
        B_000DE370[i_].f58 = 0; \
        B_000DE370[i_].f5C = 0x40; \
        B_000DE370[i_].f74 = B_000DE370[i_].f76 = 1; \
        B_000DE370[i_].f84 = B_000DE370[i_].f88 = D_000414A0; \
        B_000DE370[i_].f8C = D_000414A0 + 0x3C; \
        B_000DE370[i_].f78 = 0; \
        B_000DE370[i_].f9C = B_000DE370[i_].fA0 = D_000414A0; \
        B_000DE370[i_].fA4 = D_000414A0 + 0x3C; \
        B_000DE370[i_].f90 = B_000DE370[i_].f94 = 0; \
        B_000DE370[i_].f68 = B_000DE370[i_].f6C = -1; \
        B_000DE370[i_].fCC = B_000DE370[i_].fD0 = B_000DE370[i_].fD4 = -1; \
        B_000DE370[i_].fB0 = B_000DE370[i_].fC8 = B_000DE370[i_].fBC = B_000DE370[i_].fD8 = B_000DE370[i_].fDC = (z_);

int Sg2SlotSearchPriority(int type, int kind, int pri)
{
    volatile int ret;
    volatile int enabled;
    register float zf __asm__("$f0");
    int lo, hi, i;

    switch (type) {
    case 2:
        lo = 0; hi = 48;
        break;
    case 0:
        lo = 0; hi = 24;
        break;
    case 1:
        lo = 24; hi = 48;
        break;
    }
    enabled = DIntr();
    ret = -1;
    for (i = lo; i < hi; i++) {
        if (B_000DE370[i].f04 == kind && B_000DE370[i].f18 <= pri) {
            ret = i;
            pri = B_000DE370[i].f18;
        }
    }
    i = ret;
    if (i >= 0) {
        zf = 0;
            ret = i;
            SG2_SLOT_CLEAR(i, zf);
            B_000DE370[i].f00 = 0;
            B_000DE370[i].f04 = 5;
            B_000DE370[i].f18 = -1;
            B_000DE370[i].fC8 = zf;
            B_000DE370[i].fB0 = zf;
            B_000DE370[i].f14 = -1;
            B_000DE370[i].f0C = -1;
    }
    if (enabled)
        EIntr();
    return ret;
}
#endif
