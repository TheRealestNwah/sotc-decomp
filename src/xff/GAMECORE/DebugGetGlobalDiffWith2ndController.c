typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern struct { char pad0[0xF98]; int trig; char pad9c[0x53]; unsigned char ry; } padManagerData;
extern char iosDefaultPadData[];
extern void *get_main_cameraman_camera_obj(void);
extern char *GetLayoutClass(void *);
extern void *memset(void *, int, unsigned int);
extern void iosPadGetXZInputL(Vec4 *, void *);
extern void GetMoveVectorOnWV(Vec4 *, Vec4 *, Vec4 *, int, float);

int DebugGetGlobalDiffWith2ndController(Vec4 *out)
{
    Vec4 a;
    Vec4 pad;
    Vec4 b;
    char *cls;
    int r = 0;

    cls = GetLayoutClass(get_main_cameraman_camera_obj());
    memset(&b, 0, 0x10);
    if (padManagerData.trig & 2) {
        r = 1;
        b.f[1] = padManagerData.ry / 127.5f - 1.0f;
    }
    iosPadGetXZInputL(&pad, iosDefaultPadData + 0x78);
    pad.f[0] = pad.f[0] < 0.0f ? pad.f[0] * -pad.f[0] : pad.f[0] * pad.f[0];
    pad.f[2] = pad.f[2] < 0.0f ? pad.f[2] * -pad.f[2] : pad.f[2] * pad.f[2];
    pad.f[1] = pad.f[3] = 0.0f;
    a.q = pad.q;
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
    GetMoveVectorOnWV(out, &a, &b, *(int *)(cls + 0x164), 1.0f);
    return r;
}
