#ifdef NONMATCHING
/* 14 diffs: /7 division register choice (a0 vs v1) and final r[15] load order */
typedef unsigned long u64 __attribute__((mode(DI)));
extern int D_001359F4;
extern int getDispBufferAddressTBP(void);
extern void iosGetFontInfo(void *, int);
extern void iosFTOI4Vector(int *, float *);

typedef union { int i; float f; } IF;
typedef struct { IF unk0[4]; IF w; IF h; IF adv; IF f1C; } FontInfo;
typedef union { u64 d; float f[2]; int i[2]; void *p[2]; } PKT;

static int func_00014F18(PKT **pkt, float *r, unsigned int (*fn)(int), int arg, int shift) {
    FontInfo info;
    float xy[4];
    int ixy[4];
    unsigned int t;
    int tbp;
    int c;
    int hi;
    float u0, v0, u1, v1;
    FontInfo *fi = &info;
    float s;
    float f;

    if (r[4] > r[0] || r[5] > r[1] || r[6] < r[0] || r[7] < r[1]) {
        return 0;
    }
    iosGetFontInfo(&info, D_001359F4);
    t = fn(arg);
    if (t >= 0x200) {
        t -= 0x380;
    }
    tbp = getDispBufferAddressTBP();
    c = t >> 8;
    hi = c / 7;
    tbp += (c % 7) << 10;
    u0 = (float)(t & 0xF) * 0.0625f + 0.003f;
    v0 = (float)((t & 0xFF) >> 4) * 0.0625f + 0.003f;
    v1 = v0 + (float)fi->h.i * 0.00390625f - 0.003f;
    u1 = u0 + (float)fi->w.i * 2.0f * 0.00390625f - 0.003f;
    xy[0] = r[0] - (float)(shift * fi->w.i / 2) + (float)(shift * 3);
    xy[1] = r[1];
    s = r[15];
    f = (float)fi->w.i;
    xy[2] = xy[0] + (shift ? f * 1.3499999046325684f : f * 2.0f) * s;
    xy[3] = xy[1] + (float)fi->h.i * s;
    iosFTOI4Vector(ixy, xy);
    (*pkt)++->d = 0x56;
    (*pkt)++->d = ((u64)(tbp | 0x10000))
              | (hi ? (u64)0xC458 << 19 : (u64)0xC448 << 19)
              | (*(int *)&r[12] ? (u64)0x2007F700 << 32 : (u64)0x2007F720 << 32);
    (*pkt)++->d = (u64)*(unsigned int *)&u0 | ((u64)*(unsigned int *)&v0 << 32);
    (*pkt)++->d = (u64)(ixy[0] + 0x8000) | ((u64)(ixy[1] + 0x8000) << 16) | ((u64)-1 << 32);
    (*pkt)++->d = (u64)*(unsigned int *)&u1 | ((u64)*(unsigned int *)&v1 << 32);
    (*pkt)++->d = (u64)(ixy[2] + 0x8000) | ((u64)(ixy[3] + 0x8000) << 16) | ((u64)-1 << 32);
    r[0] += (float)((fi->w.i * 2 - fi->adv.i) >> shift) * r[15];
    return 1;
}
#endif
