typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;
typedef int u128 __attribute__((mode(TI)));

extern char *GetLayoutClass(void *);
extern void *isysGetThisSubThread(void);
extern char *GetCharacterClass(void *);
extern int ClipCollisionDirectCallBackOneObj(void *, void *, void *, void *, int, int, void *, int);
extern long nico_GetGeometryPointerAttr(void *);
extern int T_000CB4D0(void *);

static void func_000CB3A8(void *obj, char *out)
{
    char buf[0x50];
    union { Vec4 v; u128 q; } u;
    char *l = GetLayoutClass(obj);
    void *th;

    if (*(float *)(l + 0x90) == 0.0f || *(float *)(l + 0x94) == 0.0f || *(float *)(l + 0x98) == 0.0f) {
        return;
    }
    th = isysGetThisSubThread();
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
                         : : "r"(&u), "r"(*(void **)(l + 0x13C)) : "memory");
    u.q = **(u128 **)(l + 0x134);
    u.v.y += 50.0f;
    if (ClipCollisionDirectCallBackOneObj(buf, *(void **)(l + 0x134), &u,
                                          *(void **)(GetCharacterClass(th) + 0x5B4), 0, 0, T_000CB4D0, 0)) {
        *(long *)(out + 0x41B8) = nico_GetGeometryPointerAttr(buf);
        *(int *)(out + 0x41B0) = 1;
    }
}
