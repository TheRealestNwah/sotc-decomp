extern void *DldSysUndefSymbol;
typedef struct Ctx {
    char data[0x40];
} Ctx;
typedef union PairW {
    long l;
    float f[2];
} PairW;
typedef struct Pair {
    PairW a, b;
} Pair;
typedef struct Obj {
    char pad0[0x18];
    unsigned int ref;
    float radius;
} Obj;
typedef struct Slot {
    Obj *obj;
    char pad4[0x8C];
    char xform[0x30];
} Slot;
extern Slot B_0015DBD0[];
extern float IdentityQuaternion[];
extern Pair RO_00141DF0;
extern char RO_00141E00[];
extern int getDrawScreenWidth(void);
extern int getDrawScreenHeight(void);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void iosInitKPrintfContext(Ctx *, int, int, float, float, float, float, float, float);
extern void kprintfContext(Ctx *, char *, int, int);
extern int func_000E77A8(void);
extern void func_000E6100(Slot *);
extern void DEBUG_disp_sphere_object(void *, void *, void *, int, float, float, float);

static inline char *resourceData(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int mask = 0x3FFFF;
    unsigned int offset;
    char *module;
    __asm__ __volatile__("" : "+r"(mask));
    offset = encoded & mask;
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

void disp_camera_lws_animation_debug_info(void)
{
    Ctx ctx;
    Pair color;
    int i, off;
    float x, y;
    Pair *cp;

    x = (float)getDrawScreenWidth() * -0.16f;
    y = (float)getDrawScreenHeight() * 0.32f;
    iosDlPushLayer(0x18);
    iosInitKPrintfContext(&ctx, 0, 1, x, y, 1.0f, 0.6f, 0.6f, 1.0f);
    { register Ctx *c asm("$4"); int n = func_000E77A8(); c = &ctx; kprintfContext(c, RO_00141E00, n, 10); }
    iosDlPopLayer();
    iosDlPushLayer(0x17);
    cp = &RO_00141DF0;
    for (off = 0, i = 9; i >= 0; i--, off += 0xC0) {
        Slot *s = (Slot *)((char *)B_0015DBD0 + off);
        Obj *o;
        func_000E6100(s);
        o = s->obj;
        if ((o != 0) == 1 && resourceData(&o->ref) != 0) {
            float r = o->radius;
            float zz = 0.0f;
            __asm__ __volatile__("" : "+f"(zz) : : "memory");
            if (r > zz) {
            color = *cp;
            DEBUG_disp_sphere_object(s->xform, IdentityQuaternion, &color, 1, o->radius, o->radius, o->radius);
            }
        }
    }
    iosDlPopLayer();
}
