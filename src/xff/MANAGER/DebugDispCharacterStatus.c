typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
extern int strcmp(const char *, const char *);

static inline void quat_dir(void *out, void *q)
{
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
        : : "r"(out), "r"(q) : "memory");
}

static inline char *characterClass(unsigned char *object)
{
    switch (object[8]) {
    case 9: return (char *)object + 0x90;
    case 0x16: return (char *)object + 0x90;
    default: return 0;
    }
}

int DebugDispCharacterStatus(unsigned char *obj, char *name)
{
    char *c = characterClass(obj);
    Vec4 dir[2];

    if (strcmp(*(char **)(c + 0x130), name) == 0) {
        quat_dir(&dir[0], *(Vec4 **)(c + 0x13C));
        quat_dir(&dir[1], c + 0x60);
        return 1;
    }
    return 0;
}
