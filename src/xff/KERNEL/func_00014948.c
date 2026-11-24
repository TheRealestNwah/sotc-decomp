typedef unsigned long u_long64 __attribute__((mode(DI)));
typedef long s_long64 __attribute__((mode(DI)));

typedef struct { unsigned int a : 32; unsigned int b : 32; } R64;
typedef struct {
    R64 pmode;
    R64 smode2;
    R64 dispfb2;
    R64 display2;
    R64 dispfb1;
    R64 display1;
    R64 bgcolor;
} DispEnv;

typedef struct {
    int w;
    int h;
    char pad8[0x10];
    DispEnv env[2];
    char pad88[0x18];
    int A0;
    int A4;
    int A8;
    int AC;
    int B0;
} DispWork;

extern DispWork B_00065550;
extern DispEnv B_000655A0;
extern int D_00040B98;
extern int D_00040B9C;

#define SET_DISPLAY(dx, dy, magh, magv, dw, dh) \
    ((u_long64)(dx) | ((u_long64)(dy) << 12) | ((u_long64)(magh) << 23) | ((u_long64)(magv) << 27) | \
     ((u_long64)(dw) << 32) | ((u_long64)(dh) << 44))

#ifdef NONMATCHING /* 24 diffs: dh/dw register allocation (a3/t0) and branch-1 scheduling */
void func_00014948(void)
{
    DispWork *d = &B_00065550;
    DispEnv *e = &d->env[0];
    int w = d->w;
    int h = d->h;
    u_long64 dx, dy;
    s_long64 magh;
    s_long64 dw;
    int dh;
    u_long64 fb;
    u_long64 base;
    u_long64 b2;
    u_long64 b1;

    if (d->A4) {
        dx = (D_00040B98 - w + d->AC + 0x3B4) & 0xFFF;
        dy = (D_00040B9C + d->B0 + 0x34) & 0x7FF;
        dw = (s_long64)w * 2 - 1;
        dh = h - 1;
        *(u_long64 *)&e->smode2 = 2;
        *(u_long64 *)&e->pmode = 0xFF22;
        b1 = dx | ((u_long64)dh << 44) | 0x800000;
        *(u_long64 *)&e->display1 = *(u_long64 *)&e->display2 = b1 | ((dy << 12) | ((u_long64)dw << 32));
    } else {
        magh = (w + 0x9FF) / w - 1;
        dx = (D_00040B98 + 0x27C + d->AC * (magh + 1)) & 0xFFF;
        dy = (D_00040B9C + d->B0 + 0x32) & 0x7FF;
        dw = w * (magh + 1) - 1;
        dh = h - 1;
        if (d->A0) {
            *(u_long64 *)&e->pmode = 0x8023;
            *(u_long64 *)&e->smode2 = 1;
            base = dx | ((u_long64)dh << 44) | ((u_long64)magh << 23);
            *(u_long64 *)&e->display2 = base | ((dy << 12) | ((u_long64)dw << 32));
            *(u_long64 *)&e->display1 = base | (((dy + 1) << 12) | ((u_long64)dw << 32));
        } else {
            *(u_long64 *)&e->pmode = 0xFF22;
            *(u_long64 *)&e->smode2 = 3;
            b2 = dx | ((u_long64)dh << 44) | ((u_long64)magh << 23);
            *(u_long64 *)&e->display1 = *(u_long64 *)&e->display2 = b2 | ((dy << 12) | ((u_long64)dw << 32));
        }
    }
    *(u_long64 *)&e->bgcolor = 0;
    fb = ((u_long64)(w / 64) << 9) | 0x8000;
    *(u_long64 *)&e->dispfb2 = fb;
    *(u_long64 *)&e->dispfb1 = fb;
    B_000655A0 = *e;
    e = &B_000655A0;
    *(u_long64 *)&e->dispfb2 = fb;
    *(u_long64 *)&e->dispfb1 = fb;
}
#else
extern void func_00014948(void);
#endif
