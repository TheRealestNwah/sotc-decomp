typedef int s128 __attribute__((mode(TI)));

extern char gcGlobalVar[];
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern unsigned long *GetCollisionDBAttributeAdr(char *);

static inline char *getGlobals(void)
{
    return gcGlobalVar;
}

#define DT (*(float *)(getGlobals() + 0x190))
#define F(o) (*(float *)(a + (o)))
#define I(o) (*(int *)(a + (o)))

static inline int onAttr(void)
{
    char *lay = GetLayoutClass(isysGetThisSubThread());

    if (*(int *)(lay + 0x124) != 0
        && (*GetCollisionDBAttributeAdr(lay + 0xC0) & (0xF800UL << 20)) == (0xC000UL << 17))
        return 1;
    return 0;
}

static inline int inRange(char *a)
{
    if (F(0xF4) < F(0x30) && F(0xF8) < F(0x34) && -F(0x34) < F(0xF8))
        return 1;
    return 0;
}

static void func_000B1BC8(char *a)
{
    char *l2 = GetLayoutClass(*(void **)(a + 0x44));
    char *l1 = GetLayoutClass(isysGetThisSubThread());

    if (onAttr()) {
        F(0x134) += DT;
    } else {
        F(0x134) = 0;
        *(s128 *)(a + 0x110) = **(s128 **)(l1 + 0x134);
    }
    if (inRange(a)) {
        F(0x138) = 0;
    } else if (*(int *)(l1 + 0x124) != 0) {
        F(0x138) += DT;
    } else {
        F(0x138) = 0;
    }
    F(0x130) += DT;
    F(0x128) += DT;
    I(0x190) = I(0x194);
    I(0x198) = I(0x19C);
    F(0x144) = F(0x140);
    F(0x13C) = F(0x90);
    I(0x208) = I(0x1CC);
    *(s128 *)(a + 0x150) = **(s128 **)(l2 + 0x134);
    I(0x120) = inRange(a);
}
