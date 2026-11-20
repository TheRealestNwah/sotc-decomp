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

extern void iosCopyMatrix(void *, void *);
extern char *iosgluGetCameraContext(void);
extern void iosUnitRotation(void *);
extern void iosScaleMatrixV(void *, void *, void *);
extern void transMicroCode(int);
extern void iosDlLockObj(void *);
extern void iosDlChainTailCurrent(void *);

extern Hdr *B_00148730[];
extern char B_00148798[];
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);

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

void lineObjectFlip(void)
{
    Mtx cam;
    void **node;
    LineObj *obj;
    Line *l;
    void **it;
    void *last;
    int n;
    Mtx *cp;

    n = 0;
    last = 0;
    for (it = isysGroupForFirst(B_00148798, 0); it != 0; it = isysGroupForNext(it, 0)) {
        last = *it;
        n++;
    }
    if (last != 0) {
        isysGroupForExit(last, 0);
    }
    if (n != 0) {
        iosDlPushLayer(0x17);
        obj = 0;
        transMicroCode(0xB);
        iosCopyMatrix(&cam, iosgluGetCameraContext() + 0x1A0);
        for (node = isysGroupForFirst(B_00148798, 0); node != 0; node = isysGroupForNext(node, 0)) {
            obj = *node;
            cp = &cam;
            l = &obj->l;
            if (!l->f0) {
                continue;
            }
            if (l->billboard) {
                mtxMul(&l->buf[l->hdr->cur].m, cp, &obj->l.mtx);
                iosUnitRotation(&l->buf[l->hdr->cur].m);
                iosScaleMatrixV(&l->buf[l->hdr->cur].m, &l->buf[l->hdr->cur].m, obj->l.scale);
            } else {
                iosScaleMatrixV(&l->buf[l->hdr->cur].m, &obj->l.mtx, obj->l.scale);
                mtxMul(&l->buf[l->hdr->cur].m, cp, &l->buf[l->hdr->cur].m);
            }
            iosDlLockObj(obj);
            iosDlChainTailCurrent(l);
            iosDlChainTailCurrent(l->buf[l->hdr->cur].chain);
            iosDlChainTailCurrent((void *)l->hdr->dl[l->hdr->cur]);
        }
        if (obj != 0) {
            isysGroupForExit(obj, 0);
        }
        iosDlPopLayer();
    }
    for (n = 0; n < 26; n++) {
        B_00148730[n]->cur ^= 1;
    }
}
