/* NONMATCHING: 7 diffs (scheduling of the billboard bitfield store against the scale stores). */
#ifdef NONMATCHING
typedef unsigned long long u64;
typedef struct { float m[4][4]; } __attribute__((aligned(16))) Mtx;
typedef struct { int pad0; int cur; int dl[1]; } Hdr;
typedef struct { u64 tag; int w8; int wC; Mtx m; int w50; int w54; int w58; int w5C; } Buf;
typedef struct {
    u64 tag;
    int w8;
    int wC;
    int w10, w14, w18, w1C;
    u64 d20, d28, d30, d38, d40, d48, d50, d58;
    Buf buf[2];
    Mtx mtx;
    float scale[4];
    Hdr *hdr;
    unsigned int f0 : 1;
    unsigned int billboard : 1;
} Line;
typedef struct { char pad0[0x20]; Line l; } LineObj;

extern char rootPtn[];
extern int B_00148730[];
extern char B_00148798[];
extern int func_0001B338();
extern LineObj *_isysCreateObj(void *, int, int, int, void *, int);
extern char *iosgluGetCameraContext(void);
extern void iosUnitMatrix(void *);
extern int isysAddGroupWithLinkParam(void *, void *, int, int);
extern void iosCopyMatrix(void *, void *);
extern void iosUnitRotation(void *);
extern void iosScaleMatrixV(void *, void *, void *);
extern void transMicroCode(int);
extern void iosDlLockObj(void *);
extern void iosDlChainTailCurrent(void *);
extern void isysRequestDeleteObj(void *);
static inline void mtxMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%0)\n"
                         "lqc2 vf15, 0x10(%0)\n"
                         "lqc2 vf16, 0x20(%0)\n"
                         "lqc2 vf17, 0x30(%0)\n"
                         "lqc2 vf24, 0x0(%1)\n"
                         "lqc2 vf25, 0x10(%1)\n"
                         "lqc2 vf26, 0x20(%1)\n"
                         "lqc2 vf27, 0x30(%1)\n"
                         "vmulax.xyzw ACC, vf14, vf24x\n"
                         "vmadday.xyzw ACC, vf15, vf24y\n"
                         "vmaddaz.xyzw ACC, vf16, vf24z\n"
                         "vmaddw.xyzw vf24, vf17, vf24w\n"
                         "vmulax.xyzw ACC, vf14, vf25x\n"
                         "vmadday.xyzw ACC, vf15, vf25y\n"
                         "vmaddaz.xyzw ACC, vf16, vf25z\n"
                         "vmaddw.xyzw vf25, vf17, vf25w\n"
                         "vmulax.xyzw ACC, vf14, vf26x\n"
                         "vmadday.xyzw ACC, vf15, vf26y\n"
                         "vmaddaz.xyzw ACC, vf16, vf26z\n"
                         "vmaddw.xyzw vf26, vf17, vf26w\n"
                         "vmulax.xyzw ACC, vf14, vf27x\n"
                         "vmadday.xyzw ACC, vf15, vf27y\n"
                         "vmaddaz.xyzw ACC, vf16, vf27z\n"
                         "vmaddw.xyzw vf27, vf17, vf27w\n"
                         "sqc2 vf24, 0x0(%2)\n"
                         "sqc2 vf25, 0x10(%2)\n"
                         "sqc2 vf26, 0x20(%2)\n"
                         "sqc2 vf27, 0x30(%2)\n"
                         : : "r"(a), "r"(b), "r"(dst));
}

static inline LineObj *lineObjectCreate(int type, int r, int g, int b, int a, int prim, int iip)
{
    LineObj *obj;
    Line *l;
    int i;

    obj = _isysCreateObj(rootPtn, 0x1B, 0x1A0, 0x100, func_0001B338, 0x10);
    l = &obj->l;
    obj->l.hdr = (Hdr *)B_00148730[type];
    l->tag = 0x60000005;
    l->w8 = 0x10000000;
    l->wC = 0;
    l->w10 = 0x01000101;
    l->w14 = 0x03000000;
    l->w18 = 0x020001C0;
    l->w1C = 0x50000004;
    l->d20 = (0x10000000ULL << 32) | 0x8003;
    l->d28 = 0xE;
    l->d30 = (u64)(unsigned int)r | ((u64)(unsigned int)g << 8) | ((u64)(unsigned int)b << 16) | ((u64)(unsigned int)a << 24) | (0x3F800000ULL << 32);
    l->d38 = 1;
    l->d40 = iip ? 0x50000 : 0x30000;
    l->d48 = 0x47;
    switch (prim) {
    case 0:
    case 1:
        l->d50 = (0x80ULL << 32) | 0x44;
        break;
    case 2:
        l->d50 = (0x80ULL << 32) | 0x48;
        break;
    case 3:
        l->d50 = (0x80ULL << 32) | 0x42;
        break;
    }
    l->d58 = 0x42;
    iosUnitMatrix(&obj->l.mtx);
    for (i = 0; i < 2; i++) {
        Buf *p = &l->buf[i];
        p->tag = 0x60000005;
        p->w8 = 0;
        p->wC = 0x6C048000;
        mtxMul(&p->m, iosgluGetCameraContext() + 0x1A0, &l->mtx);
        p->w50 = 0x14000010;
        p->w54 = 0;
        p->w58 = 0;
        p->w5C = 0;
    }
    obj->l.f0 = 1;
    obj->l.billboard = 0;
    isysAddGroupWithLinkParam(obj, B_00148798, 0, 0);
    return obj;
}

void lineObjectDispImmediate(int type, Mtx *mtx, int r, int g, int b, int a, int prim, int iip, float sx, float sy,
                             float sz, int billboard)
{
    Mtx cam;
    LineObj *obj;
    Line *l;

    obj = lineObjectCreate(type, r, g, b, a, prim, iip);
    l = &obj->l;
    iosCopyMatrix(&l->mtx, mtx);
    obj->l.scale[0] = sx;
    obj->l.scale[1] = sy;
    obj->l.scale[2] = sz;
    obj->l.billboard = billboard;
    iosCopyMatrix(&cam, iosgluGetCameraContext() + 0x1A0);
    if (l->billboard) {
        mtxMul(&l->buf[l->hdr->cur].m, &cam, &l->mtx);
        iosUnitRotation(&l->buf[l->hdr->cur].m);
        iosScaleMatrixV(&l->buf[l->hdr->cur].m, &l->buf[l->hdr->cur].m, obj->l.scale);
    } else {
        iosScaleMatrixV(&l->buf[l->hdr->cur].m, &l->mtx, obj->l.scale);
        mtxMul(&l->buf[l->hdr->cur].m, &cam, &l->buf[l->hdr->cur].m);
    }
    transMicroCode(0xB);
    iosDlLockObj(obj);
    iosDlChainTailCurrent(l);
    iosDlChainTailCurrent(&l->buf[l->hdr->cur]);
    iosDlChainTailCurrent((void *)l->hdr->dl[l->hdr->cur]);
    isysRequestDeleteObj(obj);
}
#endif
