typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char pad0[0x10];
    int mode;
} MissileWork;

extern s128 YUnitVector;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void GetQuaternionByAxisDirZY(void *, void *, void *);
extern void UpdateLayoutClassGeometry(char *);
extern void scrRunM(int);
extern void isysJumpSubThread(void (*)(MissileWork *), MissileWork *);
extern void func_0006C328(MissileWork *);

static void T_0006CF58(MissileWork *w)
{
    void *th = isysGetThisSubThread();
    char *lay = GetLayoutClass(th);
    float speed = 0.0f;
    Vec4 dir;
    Vec4 n;
    char *l2;

    switch (w->mode) {
    case 0:
        speed = 200.0f;
        break;
    case 1:
        speed = 140.0f;
        break;
    case 2:
    case 3:
        speed = 160.0f;
        break;
    case 4:
        speed = 300.0f;
        break;
    default:
        w->mode = -1;
        break;
    }
    __asm__ __volatile__("lqc2 vf4, 0x0(%1)\n"
                         "vmul.xyzw vf5, vf4, vf4\n"
                         "vmr32.xyzw vf6, vf4\n"
                         "vmul.xyzw vf7, vf6, vf4\n"
                         "vmr32.xyzw vf6, vf6\n"
                         "vmul.xyzw vf8, vf6, vf4\n"
                         "vsubx.z vf6, vf0, vf5x\n"
                         "vsuby.z vf6, vf6, vf5y\n"
                         "vaddw.y vf6, vf7, vf7w\n"
                         "vsuby.x vf6, vf8, vf8y\n"
                         "vsub.w vf6, vf0, vf0\n"
                         "vadd.w vf5, vf0, vf0\n"
                         "vmulw.xyz vf6, vf6, vf5w\n"
                         "vaddw.z vf6, vf6, vf0w\n"
                         "sqc2 vf6, 0x0(%0)\n"
                         : : "r"(&dir), "r"(*(void **)(lay + 0x13C)) : "memory");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyzw vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(lay + 0x30), "r"(&dir), "r"(speed * 1000.0f / 3600.0f) : "memory");
    l2 = GetLayoutClass(th);
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "vmul.xyz vf7, vf5, vf5\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vrsqrt Q, vf0w, vf7w\n"
                         "vwaitq\n"
                         "vmulq.xyz vf5, vf5, Q\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(&n), "r"(l2 + 0x30) : "memory");
    GetQuaternionByAxisDirZY(*(void **)(l2 + 0x13C), &n, &YUnitVector);
    UpdateLayoutClassGeometry(lay);
    scrRunM(1);
    isysJumpSubThread(func_0006C328, w);
}
