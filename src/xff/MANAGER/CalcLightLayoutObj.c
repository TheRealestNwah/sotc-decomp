#ifdef NONMATCHING /* 138 diffs: rough draft; parent-chain walk (0x124/0x198, GetGeometryPointerObject/GetCharacterClass/GetLayoutClass, shorts 0x370 == 3/2) and 64-bit flag copies at 0x260/0xC0; one VU0 run (matrix apply) in place */
typedef int s128 __attribute__((mode(TI)));
typedef long long s64;
typedef unsigned long long u64;

extern char *GetLayoutClass(void *);
extern char *GetCharacterClass(void *);
extern void *GetGeometryPointerObject(void *);
extern void SetGeoDispClassLightColMan(void *);
extern void iosScaleNormalLightMatrix(void *, void *, void *);
extern void iosCopyMatrix(void *, void *);
extern void glSetLightColor(void *);
extern void glSetLightVector(void *);

void CalcLightLayoutObj(void *obj)
{
    char *c = GetLayoutClass(obj);
    char *lightData;
    char *node;
    char *t;
    void *cur;
    char *cls;
    char *cc;
    char *a, *b;
    char *dst;
    void *pos;
    float *mat;

    if (*(u64 *)(*(char **)(c + 0x144) + 0x260) & 2) {
        lightData = *(char **)(c + 0x140);
        cur = obj;
        node = GetLayoutClass(cur);
        if (*(int *)(node + 0x124) == 0) {
            *(int *)(node + 0x198) = 0;
        } else {
            void *parent = 0;
            for (;;) {
                if (*(int *)(node + 0x124) == 0) {
                    *(void **)(node + 0x198) = parent;
                    break;
                }
                a = (char *)GetGeometryPointerObject(node + 0xC0);
                cc = GetCharacterClass(cur);
                b = GetCharacterClass(a);
                cls = GetLayoutClass(a);
                if (cls == 0)
                    goto done;
                if (cc == 0 || b == 0)
                    continue;
                if (*(short *)(cls + 0x370) == 3 || *(short *)(b + 0x370) == 2)
                    continue;
                goto done;
            }
        }
done:
        if (*(int *)(c + 0x198) != 0)
            return;
        {
            char *d = *(char **)(c + 0x144);
            char *ld = *(char **)(c + 0x140);
            float *m = (float *)(*(char **)(c + 0x15C));
            char *geo = *(char **)(*(char **)d + 0x20);
            __asm__ __volatile__("lqc2 vf8, 0x0(%0)\n"
                                 "lqc2 vf14, 0x0(%1)\n"
                                 "lqc2 vf15, 0x10(%1)\n"
                                 "lqc2 vf16, 0x20(%1)\n"
                                 "lqc2 vf17, 0x30(%1)\n"
                                 "vmulax.xyzw ACC, vf14, vf8x\n"
                                 "vmadday.xyzw ACC, vf15, vf8y\n"
                                 "vmaddaz.xyzw ACC, vf16, vf8z\n"
                                 "vmaddw.xyzw vf10, vf17, vf0w\n"
                                 "sqc2 vf10, 0x0(%2)\n"
                                 : : "r"(geo + 0x20), "r"(m), "r"(ld + 0x10) : "memory");
        }
        dst = (char *)obj;
        *(float *)(*(char **)(c + 0x140) + 0x1C) = *(float *)(*(char **)(c + 0x144) + 0x250) * *(float *)(*(char **)(*(char **)(c + 0x144)) + 0x20 + 0x2C);
        *(u64 *)(*(char **)(c + 0x140) + 0xC0) = (*(u64 *)(*(char **)(c + 0x140) + 0xC0) & ~1ULL) | ((*(u64 *)(*(char **)(c + 0x144) + 0x260) >> 2) & 1);
        *(int *)((char *)obj + 0xEC) = *(int *)(c + 0x130);
        SetGeoDispClassLightColMan(obj);
        iosScaleNormalLightMatrix((char *)obj + 0x40, (char *)obj + 0x40, c + 0x90);
        *(u64 *)(*(char **)(c + 0x144) + 0x260) = (*(u64 *)(*(char **)(c + 0x144) + 0x260) & ~8ULL) | (((*(u64 *)(*(char **)(c + 0x140) + 0xC0) >> 1) & 1) << 3);
        iosCopyMatrix(*(char **)(*(char **)(c + 0x144) + 0xC) + 0x50, (char *)obj + 0x80);
        iosCopyMatrix(*(char **)(*(char **)(c + 0x144) + 0xC) + 0x10, (char *)obj + 0x40);
        glSetLightColor(*(char **)(*(char **)(c + 0x144) + 0xC) + 0x50);
        glSetLightVector(*(char **)(*(char **)(c + 0x144) + 0xC) + 0x10);
    }
}
#endif
