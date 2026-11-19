typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern struct { char pad[0x170]; float speed; } gcGlobalVar;
extern char iosDefaultPadData[];
extern void *get_main_cameraman_camera_obj(void);
extern char *GetLayoutClass(void *);
extern void *memset(void *, int, unsigned int);
extern void iosPadGetXZInputR(Vec4 *, void *);
extern void GetMoveVectorOnWV(Vec4 *, Vec4 *, Vec4 *, int, float);

static inline void vecAdd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

int DebugGlobalMoveWith1stController(Vec4 *out, Vec4 *in)
{
    Vec4 a;
    Vec4 pad;
    Vec4 b;
    Vec4 mv;
    char *cls;

    cls = GetLayoutClass(get_main_cameraman_camera_obj());
    memset(&a, 0, 0x10);
    memset(&b, 0, 0x10);
    iosPadGetXZInputR(&pad, iosDefaultPadData);
    pad.f[0] = pad.f[0] < 0.0f ? pad.f[0] * -pad.f[0] : pad.f[0] * pad.f[0];
    pad.f[2] = pad.f[2] < 0.0f ? pad.f[2] * -pad.f[2] : pad.f[2] * pad.f[2];
    pad.f[1] = pad.f[3] = 0.0f;
    vecAdd(&a, &a, &pad);
    {
        float v = b.f[1];
        float r;
        if (!(v < 0.0f ? -0.39999998f < v : v < 0.39999998f))
            r = (b.f[1] < 0.0f ? -1.0f : 1.0f) * ((b.f[1] < 0.0f ? -0.39999998f - b.f[1] : b.f[1] - 0.39999998f) * (1.0f / (1.0f - 0.39999998f)));
        else
            r = 0.0f;
        b.f[1] = r;
    }
    b.f[1] = b.f[1] < 0.0f ? b.f[1] * -b.f[1] : b.f[1] * b.f[1];
    a.f[0] = -a.f[0];
    GetMoveVectorOnWV(&mv, &a, &b, *(int *)(cls + 0x164), gcGlobalVar.speed * 30.0f);
    vecAdd(out, in, &mv);
    return 0;
}
