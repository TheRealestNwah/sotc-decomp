typedef struct { float m[4][4]; } __attribute__((aligned(16))) Mtx;
typedef struct { int pad0; int cur; int dl[1]; } Hdr;
typedef struct { char chain[0x10]; Mtx m; char pad50[0x10]; } Buf;
typedef struct {
    char pad0[0x60];
    Buf buf[2];
    Mtx mtx;
    float scale[4];
    Hdr *hdr;
    unsigned int f0 : 1;
    unsigned int billboard : 1;
} Line;
typedef struct { char pad0[0x20]; Line l; } LineObj;

extern LineObj *lineObjectCreatef(int, int, int, float, float, float, float);
extern void iosCopyMatrix(void *, void *);
extern char *iosgluGetCameraContext(void);
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

#define BUF(l) ((l)->body + (l)->hdr->cur * 0x60)

void lineObjectDispImmediatef(int type, Mtx *mtx, int a2, int a3, float sx, float sy, float sz, float r, float g,
                              float b, float a, int billboard)
{
    Mtx cam;
    LineObj *obj;
    Line *l;

    obj = lineObjectCreatef(type, a2, a3, r, g, b, a);
    l = &obj->l;
    iosCopyMatrix(&obj->l.mtx, mtx);
    obj->l.scale[0] = sx;
    obj->l.scale[1] = sy;
    obj->l.scale[2] = sz;
    obj->l.billboard = billboard;
    iosCopyMatrix(&cam, iosgluGetCameraContext() + 0x1A0);
    if (l->billboard) {
        mtxMul(&l->buf[l->hdr->cur].m, &cam, &obj->l.mtx);
        iosUnitRotation(&l->buf[l->hdr->cur].m);
        iosScaleMatrixV(&l->buf[l->hdr->cur].m, &l->buf[l->hdr->cur].m, obj->l.scale);
    } else {
        iosScaleMatrixV(&l->buf[l->hdr->cur].m, &obj->l.mtx, obj->l.scale);
        mtxMul(&l->buf[l->hdr->cur].m, &cam, &l->buf[l->hdr->cur].m);
    }
    transMicroCode(0xB);
    iosDlLockObj(obj);
    iosDlChainTailCurrent(l);
    iosDlChainTailCurrent(l->buf[l->hdr->cur].chain);
    iosDlChainTailCurrent((void *)l->hdr->dl[l->hdr->cur]);
    isysRequestDeleteObj(obj);
}
