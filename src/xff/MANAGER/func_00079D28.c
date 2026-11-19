typedef long long s64;
typedef unsigned long long u64;
typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; u64 d; float f; } U;
#define ST(T, a) (((U *)(a))->T)

extern void LoopExecPreLightColMan(void);
extern void LoopExecAfterLightColMan(void);
extern char *iosgluGetCameraContext(void);
extern void SetCameraReverbFlag(void *);
extern int *GetFirstSortObj(void *);
extern int *GetNextSortObj(void *, int *);
extern char *GetLayoutClass(int);
extern char *GetGeoDispClass(int);
extern void iosCopyMatrix(void *, void *);
extern void func_00079788(int, char *);

typedef void (*DispFn)(int);

static void func_00079D28(void *list)
{
    int *s;

    LoopExecPreLightColMan();
    SetCameraReverbFlag(iosgluGetCameraContext() + 0x140);

    for (s = GetFirstSortObj(list); s != 0; s = GetNextSortObj(list, s)) {
        int obj = *s;
        char *lc = GetLayoutClass(obj);
        if (lc != 0) {
            char *l = *(char **)(lc + 0x140);
            if ((*(u64 *)(*(char **)(lc + 0x144) + 0x260) & 2) && l != 0 && *(DispFn *)(l + 0xE0) != 0)
                (*(DispFn *)(l + 0xE0))(obj);
        } else {
            char *g = GetGeoDispClass(obj);
            if (g != 0 && *(DispFn *)(g + 0xE0) != 0)
                (*(DispFn *)(g + 0xE0))(obj);
        }
    }

    for (s = GetFirstSortObj(list); s != 0; s = GetNextSortObj(list, s)) {
        int obj = *s;
        float f;
        char *c = GetLayoutClass(obj);
        if (c != 0) {
            char *d = *(char **)(c + 0x144);
            char *l = *(char **)(c + 0x140);
            if ((*(u64 *)(d + 0x260) & 2) && l != 0 && *(DispFn *)(l + 0xE0) != 0 && *(int *)(c + 0x198) == 0)
                func_00079788(obj, d);
            d = *(char **)(c + 0x144);
            f = *(float *)(*(char **)(*(char **)(*(char **)d + 0x20) + 0x8) + 0x2C);
            if (f != 1.0f) {
                char *v = *(char **)(d + 0xC) + 0x80;
                __asm__ __volatile__("lqc2 vf5, 0x0(%0)\nqmtc2.ni %1, vf6\nvmulx.xyzw vf5, vf5, vf6x\nsqc2 vf5, 0x0(%0)\n" : : "r"(v), "r"(f) : "memory");
            }
        }
    }

    for (s = GetFirstSortObj(list); s != 0; s = GetNextSortObj(list, s)) {
        char *c = GetLayoutClass(*s);
        char *p;
        char *l;
        if (c == 0)
            continue;
        l = *(char **)(c + 0x140);
        if ((*(u64 *)(*(char **)(c + 0x144) + 0x260) & 2) && l != 0 && *(DispFn *)(l + 0xE0) != 0 && *(int *)(c + 0x198) != 0) {
            p = GetLayoutClass(*(int *)(c + 0x198));
            ST(q, *(char **)(c + 0x140) + 0x10) = *(s128 *)(*(char **)(p + 0x140) + 0x10);
            ST(d, *(char **)(c + 0x140) + 0xC0) = (*(u64 *)(*(char **)(c + 0x140) + 0xC0) & ~1ULL) | (*(unsigned char *)(*(char **)(p + 0x140) + 0xC0) & 1);
            ST(d, *(char **)(c + 0x144) + 0x260) = (*(u64 *)(*(char **)(c + 0x144) + 0x260) & ~8ULL) | ((((unsigned short)(*(u64 *)(*(char **)(p + 0x144) + 0x260) >> 3)) & 1) << 3);
            iosCopyMatrix(*(char **)(*(char **)(c + 0x144) + 0xC) + 0x50, *(char **)(*(char **)(p + 0x144) + 0xC) + 0x50);
            iosCopyMatrix(*(char **)(*(char **)(c + 0x144) + 0xC) + 0x10, *(char **)(*(char **)(p + 0x144) + 0xC) + 0x10);
            ST(f, *(char **)(*(char **)(c + 0x144) + 0xC) + 0xD4) = *(float *)(*(char **)(*(char **)(p + 0x144) + 0xC) + 0xD4);
            ST(f, *(char **)(*(char **)(c + 0x144) + 0xC) + 0xD8) = *(float *)(*(char **)(*(char **)(p + 0x144) + 0xC) + 0xD8);
        }
    }

    LoopExecAfterLightColMan();
}
