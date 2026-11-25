typedef int s128 __attribute__((mode(TI)));
typedef struct { s128 m[4]; } Mat;

extern void iosScaleMatrixV(void *, void *, void *);
extern void iosGetScaleMatrixV(void *, void *);
extern void iosGetScaleInverseVector(void *, void *);

static inline void matInverse(void *dst, void *src)
{
    __asm__ __volatile__("lqc2 vf24, 0x30(%1)\n"
                         "vsubw.x vf25, vf0, vf0w\n"
                         "vmulx.xyz vf28, vf24, vf25x\n"
                         "vsub.w vf28, vf28, vf28\n"
                         "lq $8, 0x0(%1)\n"
                         "lq $9, 0x10(%1)\n"
                         "lq $10, 0x20(%1)\n"
                         "qmfc2.ni $11, vf0\n"
                         "pextlw $12, $9, $8\n"
                         "pextuw $13, $9, $8\n"
                         "pextlw $14, $11, $10\n"
                         "pextuw $15, $11, $10\n"
                         "pcpyld $8, $14, $12\n"
                         "pcpyud $9, $12, $14\n"
                         "pcpyld $10, $15, $13\n"
                         "pcpyud $11, $13, $15\n"
                         "qmtc2.ni $8, vf24\n"
                         "qmtc2.ni $9, vf25\n"
                         "qmtc2.ni $10, vf26\n"
                         "vmulax.xyzw ACC, vf24, vf28x\n"
                         "vmadday.xyzw ACC, vf25, vf28y\n"
                         "vmaddaz.xyzw ACC, vf26, vf28z\n"
                         "vmaddw.xyzw vf29, vf0, vf28w\n"
                         "vsub.w vf29, vf29, vf29\n"
                         "vadd.w vf29, vf29, vf0\n"
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf29, 0x30(%0)\n"
                         : : "r"(dst), "r"(src) : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "memory");
}

static inline void matMul(void *dst, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n"
                         "lqc2 vf15, 0x10(%1)\n"
                         "lqc2 vf16, 0x20(%1)\n"
                         "lqc2 vf17, 0x30(%1)\n"
                         "lqc2 vf24, 0x0(%2)\n"
                         "lqc2 vf25, 0x10(%2)\n"
                         "lqc2 vf26, 0x20(%2)\n"
                         "lqc2 vf27, 0x30(%2)\n"
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
                         "sqc2 vf24, 0x0(%0)\n"
                         "sqc2 vf25, 0x10(%0)\n"
                         "sqc2 vf26, 0x20(%0)\n"
                         "sqc2 vf27, 0x30(%0)\n"
                         : : "r"(dst), "r"(a), "r"(b) : "memory");
}

static inline void quatToMat(void *m0, void *q0, void *p0)
{
    register void *m asm("$2") = m0;
    register void *q asm("$3") = q0;
    register void *p asm("$4") = p0;
    __asm__ __volatile__("vaddw.xyz vf12, vf0, vf0w
"
                         "lqc2 vf11, 0x0(%1)
"
                         "vmr32.w vf14, vf0
"
                         "vmr32.w vf15, vf0
"
                         "vmr32.w vf16, vf0
"
                         "vopmula.xyz ACC, vf11, vf12
"
                         "vmadd.xyz vf11, vf0, vf0
"
                         "vmadd.xyz vf10, vf11, vf12
"
                         "vmul.xyz vf13, vf11, vf10
"
                         "vopmula.xyz ACC, vf11, vf10
"
                         "vmaddw.xyz vf15, vf10, vf11w
"
                         "vmsubw.xyz vf16, vf10, vf11w
"
                         "vopmula.xyz ACC, vf13, vf12
"
                         "vmadd.xyz vf17, vf13, vf12
"
                         "vopmula.xyz ACC, vf15, vf12
"
                         "vmadd.xyz vf15, vf0, vf0
"
                         "vsub.xyz vf14, vf12, vf17
"
                         "vmove.yz vf17, vf14
"
                         "vmove.y vf14, vf16
"
                         "vmove.y vf16, vf15
"
                         "vmove.y vf15, vf17
"
                         "vmove.z vf14, vf15
"
                         "vmove.z vf15, vf16
"
                         "vmove.z vf16, vf17
"
                         "sqc2 vf14, 0x0(%0)
"
                         "sqc2 vf15, 0x10(%0)
"
                         "sqc2 vf16, 0x20(%0)
"
                         "lqc2 vf4, 0x0(%2)
"
                         "vmove.w vf4, vf0
"
                         "sqc2 vf4, 0x30(%0)
"
                         : : "r"(m), "r"(q), "r"(p) : "memory");
}

extern s128 ZeroVector;

static inline void updateGeo(char *l)
{
    Mat sm;
    Mat tmp;
    float sv[4] __attribute__((aligned(16)));
    float inv[4] __attribute__((aligned(16)));
    Mat a;
    Mat b;
    int n;
    int m;
    Mat *src;
    Mat *fp;

    n = *(short *)(l + 0x1B4);
    if (!(*(unsigned char *)(l + 0x1BC) & 2))
        goto end;
    src = *(Mat **)(l + 0x158);
    if (*(unsigned char *)(l + 0x1BC) & 0x10) {
        Mat *p = src;
        Mat *dst = *(Mat **)(l + 0x164);
        int i = n - 1;
        if (n != 0) {
            do {
                matInverse(dst, p);
                i--;
                dst++;
                p++;
            } while (i != -1);
        }
    }
    if (!(*(unsigned char *)(l + 0x1BC) & 4))
        goto end;
    m = n - 1;
    fp = *(Mat **)(l + 0x15C);
    {
        char *sc = l + 0x90;
        Mat *p = fp;
        Mat *q = src;
        int i;
        for (i = m; i != -1; i--) {
            iosScaleMatrixV(p, q, sc);
            p++;
            q++;
        }
    }
    if (*(unsigned char *)(l + 0x1BC) & 0x40) {
        Mat *r = *(Mat **)(l + 0x16C);
        Mat *q = *(Mat **)(l + 0x168);
        Mat *p = fp;
        int i;
        iosGetScaleMatrixV(&sm, l + 0xB0);
        for (i = m; i != -1; i--) {
            matMul(&tmp, &sm, q);
            matMul(r, p, &tmp);
            r++;
            p++;
            q++;
        }
    }
    if (*(unsigned char *)(l + 0x1BC) & 0x80) {
        Mat *r = *(Mat **)(l + 0x170);
        Mat *q = *(Mat **)(l + 0x168);
        Mat *p = *(Mat **)(l + 0x164);
        int i = n;
        iosGetScaleInverseVector(inv, l + 0xB0);
        {
        register float *svp asm("$5") = sv;
        register float *ip asm("$3") = inv;
        register char *ap asm("$2") = l + 0xA0;
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                             "lqc2 vf6, 0x0(%1)\n"
                             "vmul.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%2)\n"
                             : : "r"(ip), "r"(ap), "r"(svp) : "memory");
        }
        iosGetScaleMatrixV(&tmp, sv);
        for (i--; i != -1; i--) {
            matMul(&a, &tmp, p);
            matInverse(&b, q);
            matMul(r, &b, &a);
            r++;
            p++;
            q++;
        }
    }
end:
    ;
}

void UpdateLayoutClassSimpleGeometry(char *l, float dt)
{
    if (*(unsigned char *)(l + 0x1BC) & 1)
        **(s128 **)(l + 0x154) = **(s128 **)(l + 0x13C);
    if (*(unsigned char *)(l + 0x1BC) & 2) {
        quatToMat(*(void **)(l + 0x158), *(void **)(l + 0x13C), *(void **)(l + 0x134));
    }
    updateGeo(l);
    if (dt != 0.0f) {
        float *v = (float *)(l + 0x30);
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                             "lqc2 vf6, 0x0(%2)
"
                             "vsub.xyzw vf7, vf5, vf6
"
                             "sqc2 vf7, 0x0(%0)
"
                             : : "r"(v), "r"(*(void **)(l + 0x134)), "r"(*(void **)(l + 0x138)) : "memory");
        __asm__ __volatile__("lqc2 vf5, 0x0(%0)
"
                             "qmtc2.ni %1, vf6
"
                             "vmulx.xyz vf5, vf5, vf6x
"
                             "sqc2 vf5, 0x0(%0)
"
                             : : "r"(v), "r"(dt) : "memory");
    } else {
        *(s128 *)(l + 0x30) = ZeroVector;
    }
}
