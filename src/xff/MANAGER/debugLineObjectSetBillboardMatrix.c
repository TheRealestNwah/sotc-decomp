typedef int s128 __attribute__((mode(TI)));
/* dst = a * b */
#define VU_MUL_MATRIX(dst, a, b) \
    __asm__ __volatile__("lqc2 vf14, 0x0(%1)\n" \
                         "lqc2 vf15, 0x10(%1)\n" \
                         "lqc2 vf16, 0x20(%1)\n" \
                         "lqc2 vf17, 0x30(%1)\n" \
                         "lqc2 vf24, 0x0(%2)\n" \
                         "lqc2 vf25, 0x10(%2)\n" \
                         "lqc2 vf26, 0x20(%2)\n" \
                         "lqc2 vf27, 0x30(%2)\n" \
                         "vmulax.xyzw ACC, vf14, vf24x\n" \
                         "vmadday.xyzw ACC, vf15, vf24y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf24z\n" \
                         "vmaddw.xyzw vf24, vf17, vf24w\n" \
                         "vmulax.xyzw ACC, vf14, vf25x\n" \
                         "vmadday.xyzw ACC, vf15, vf25y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf25z\n" \
                         "vmaddw.xyzw vf25, vf17, vf25w\n" \
                         "vmulax.xyzw ACC, vf14, vf26x\n" \
                         "vmadday.xyzw ACC, vf15, vf26y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf26z\n" \
                         "vmaddw.xyzw vf26, vf17, vf26w\n" \
                         "vmulax.xyzw ACC, vf14, vf27x\n" \
                         "vmadday.xyzw ACC, vf15, vf27y\n" \
                         "vmaddaz.xyzw ACC, vf16, vf27z\n" \
                         "vmaddw.xyzw vf27, vf17, vf27w\n" \
                         "sqc2 vf24, 0x0(%0)\n" \
                         "sqc2 vf25, 0x10(%0)\n" \
                         "sqc2 vf26, 0x20(%0)\n" \
                         "sqc2 vf27, 0x30(%0)\n" \
                         : : "r"(dst), "r"(a), "r"(b) : "memory")

typedef struct {
    unsigned long long w[8];
} LinePacket;

extern LinePacket D_00135CA0;
extern void *iosAllocPacketPtrPath1(int);
extern char *iosgluGetCameraContext(void);
extern void iosUnitRotation(float *);
extern void iosScaleMatrixV(float *, float *, float *);
extern void iosDlChainTailCurrent(void *);

void debugLineObjectSetBillboardMatrix(float *matrix, float sx, float sy, float sz)
{
    float m[4][4] __attribute__((aligned(16)));
    LinePacket *pkt = iosAllocPacketPtrPath1(0x40);
    float scale[4] __attribute__((aligned(16))) = {sx, sy, sz, 1.0f};
    float *p;
    int i, j;

    *pkt = D_00135CA0;
    VU_MUL_MATRIX(m, iosgluGetCameraContext() + 0x1A0, matrix);
    iosUnitRotation(&m[0][0]);
    iosScaleMatrixV(&m[0][0], &m[0][0], scale);
    i = 0;
    p = (float *)pkt + 3;
    for (; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            p[i * 3 + j] = m[i][j];
        }
    }
    iosDlChainTailCurrent(pkt);
}
