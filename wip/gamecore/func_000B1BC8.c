typedef int s128 __attribute__((mode(TI)));

struct GcGlobal { char pad[0x190]; float delta; };
extern struct GcGlobal gcGlobalVar;
extern char *GetLayoutClass(int);
extern int isysGetThisSubThread(void);
extern unsigned long *GetCollisionDBAttributeAdr(void *);

static inline int func_000B1BC8_onGround(char *layout)
{
    int ret = 0;
    if (*(int *)(layout + 0x124) != 0) {
        unsigned long a = *GetCollisionDBAttributeAdr(layout + 0xC0) & (0xF800UL << 20);
        ret = 1;
        if (a != (0xC000UL << 17))
            ret = 0;
    }
    return ret;
}

static inline int func_000B1BC8_inRange(char *obj)
{
    int ret = 0;
    if (*(float *)(obj + 0xF4) < *(float *)(obj + 0x30) && *(float *)(obj + 0xF8) < *(float *)(obj + 0x34)) {
        ret = 1;
        if (!(-*(float *)(obj + 0x34) < *(float *)(obj + 0xF8)))
            ret = 0;
    }
    return ret;
}

void func_000B1BC8(char *obj)
{
    char *target = GetLayoutClass(*(int *)(obj + 0x44));
    char *self = GetLayoutClass(isysGetThisSubThread());

    if (func_000B1BC8_onGround(GetLayoutClass(isysGetThisSubThread()))) {
        *(float *)(obj + 0x134) += gcGlobalVar.delta;
    } else {
        *(float *)(obj + 0x134) = 0.0f;
        *(s128 *)(obj + 0x110) = **(s128 **)(self + 0x134);
    }

    if (!func_000B1BC8_inRange(obj) && *(int *)(self + 0x124) != 0) {
        *(float *)(obj + 0x138) += gcGlobalVar.delta;
    } else {
        *(float *)(obj + 0x138) = 0.0f;
    }

    *(float *)(obj + 0x130) += gcGlobalVar.delta;
    *(int *)(obj + 0x190) = *(int *)(obj + 0x194);
    *(int *)(obj + 0x198) = *(int *)(obj + 0x19C);
    *(float *)(obj + 0x144) = *(float *)(obj + 0x140);
    *(float *)(obj + 0x13C) = *(float *)(obj + 0x90);
    *(int *)(obj + 0x208) = *(int *)(obj + 0x1CC);
    *(float *)(obj + 0x128) += gcGlobalVar.delta;
    *(s128 *)(obj + 0x150) = **(s128 **)(target + 0x134);
    *(int *)(obj + 0x120) = func_000B1BC8_inRange(obj);
}
