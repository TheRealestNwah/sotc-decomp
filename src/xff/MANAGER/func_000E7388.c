typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern void *DldSysUndefSymbol;

typedef struct {
    char pad0[0x18];
    unsigned int ref;
    float radius;
} EffectDef;

typedef struct {
    char pad0[0x90];
    Vec4 pos;
    char padA0[0xB4 - 0xA0];
    int active;
} EffectObj;

typedef struct {
    char pad0[0x134];
    float *pos;
} LayoutClass;

extern LayoutClass *GetLayoutClass(void *);
extern void fsEffectSetParam(void *);

static inline void *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;
    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

static inline float distSq(float *a, float *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%2)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(b), "r"(a) : "$2");
    return d;
}

static void func_000E7388(EffectObj *obj, EffectDef *def, void *layout)
{
    void *data = resourceData(&def->ref);
    int active;

    if (!data)
        return;
    active = obj->active;
    if (active == 0) {
        float r = def->radius;

        if (r < 0.0f) {
            obj->active = 1;
            active = 1;
        } else if (layout) {
            LayoutClass *cls;
            int one;

            r = r * r;
            cls = GetLayoutClass(layout);
            one = 1;
            if (distSq(obj->pos.f, cls->pos) <= r) {
                obj->active = 1;
                active = one;
            } else {
                active = obj->active;
            }
        }
    }
    if (active == 1)
        return fsEffectSetParam(data);
}
