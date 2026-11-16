#ifdef NONMATCHING /* 113 diffs: frame 0xD0 vs 0xC0 (extra saved reg), statics hi/lo addressing differs */
typedef int s128 __attribute__((mode(TI)));

extern unsigned char B_00149A00[];
extern int D_001370D0;
extern void *iosgluGetCameraContext(void);
extern void iosCopyMatrix(void *, void *);
extern void iosTransposeMatrix(void *, void *);
extern void create_original_view_matrix(void *, void *, void *, void *);
extern int GetWaterSurfacePositionYExtend(float, float, float, void *, void *, int, int);
extern int ClipCollisionVariableXZSurfaceNoBottomCheck(void *, void *, void *, int);
extern int IsWaterSurfaceExistAround(void *, void *, int, float, float);
extern int *getFogUnderWater(void);
extern char ZeroPoint[], YUnitVector[];

void func_000BF318(int mode)
{
    s128 buf[8];
    char *cam = (char *)iosgluGetCameraContext();
    unsigned char *b = B_00149A00;
    unsigned char *b2;
    unsigned char *m;
    float zero = 0.0f;
    int *fog;

    iosCopyMatrix(b, cam + 0x1A0);
    *(float *)(b + 0x38) = zero;
    *(float *)(b + 0x34) = zero;
    iosTransposeMatrix(b, b);
    *(float *)(b + 0x30) = zero;
    buf[0] = *(s128 *)(cam + 0x150);
    *(float *)((char *)buf + 4) = zero;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(buf) : "memory");
    m = b + 0x40;
    create_original_view_matrix(m, ZeroPoint, buf, YUnitVector);
    iosTransposeMatrix(m, m);
    *(float *)(b + 0x88) = *(float *)(b + 0x84);
    if (mode == 1) {
        *(int *)(b + 0x80) = GetWaterSurfacePositionYExtend(100.0f, -500.0f, 1.0f, b + 0x84, cam + 0x140, D_001370D0, 1);
    } else {
        buf[6] = *(s128 *)(cam + 0x140);
        *(float *)((char *)buf + 0x64) = 100.0f;
        buf[7] = *(s128 *)(cam + 0x140);
        *(float *)((char *)buf + 0x74) = -500.0f;
        if (ClipCollisionVariableXZSurfaceNoBottomCheck(&buf[1], &buf[6], &buf[7], D_001370D0)) {
            *(int *)(b + 0x80) = 1;
            *(float *)(b + 0x84) = *(float *)((char *)buf + 0x54);
        } else {
            *(int *)(b + 0x80) = 0;
        }
    }
    b2 = B_00149A00;
    if (*(int *)(b2 + 0x80) == 0) {
        *(int *)(b2 + 0x80) = IsWaterSurfaceExistAround(b2 + 0x84, cam + 0x140, D_001370D0, 50.0f, 1.0f);
        if (*(int *)(b2 + 0x80) == 0)
            *(float *)(b2 + 0x84) = -10000.0f;
        b2 = B_00149A00;
    }
    *(float *)(b2 + 0x8C) = *(float *)(b2 + 0x84) - *(float *)(b2 + 0x88);
    fog = getFogUnderWater();
    *(int *)(b2 + 0x90) = *fog != 0;
}
#endif
