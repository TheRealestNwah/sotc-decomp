extern void *DldSysUndefSymbol;
extern int strcmp(const char *, const char *);
typedef struct { const char *name; char rest[112]; } AnimationDefinition;
typedef union {
    struct {
        int f0;
        int f4;
        float f8;
        float fC;
        char pad10[8];
        int f18;
        float f1C;
        int f20;
        int f24;
        float f28;
        float f2C;
        char table[1];
    } s;
    char alias;
} AnimationClass;
typedef struct {
    int pad;
    short frames;
} AnimResource;
extern void ResetAnimeFrameTableInfo(void *, int, int);
extern void func_0003F860(int **, void *, void *);
extern void *_isysCreateObj(void *, int, int, int, int, int);

static void func_0003FF78(void);

static inline char *resourceModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    if (offset)
        return *(char **)((char *)reference - offset);
    return 0;
}

static inline int resourceCount(unsigned int *reference)
{
    char *module = resourceModule(reference);
    if (module && module != DldSysUndefSymbol)
        return *(int *)(module + 0xC);
    return 0;
}

static inline AnimationDefinition *resourceEntries(unsigned int *reference)
{
    char *module = resourceModule(reference);
    if (module && module != DldSysUndefSymbol)
        return *(AnimationDefinition **)(module + 0x10);
    return 0;
}

static inline AnimationDefinition *findDefinition(AnimationDefinition *entry, int count, const char *name)
{
    int remaining;
    for (remaining = count - 1; remaining != -1; --remaining, ++entry) {
        if (strcmp(entry->name, name) == 0)
            return entry;
    }
    return 0;
}

int SetAnimationClassLastInfoDirectResource(AnimationClass *anim, AnimResource *res)
{
    float last = res->frames - 1;

    anim->s.f0 = 0;
    anim->s.f4 = 0;
    anim->s.f8 = last;
    anim->s.fC = last;
    anim->s.f18 = 0;
    anim->s.f1C = 1.0f;
    anim->s.f20 = 0;
    anim->s.f24 = 0;
    anim->s.f28 = 1.0f;
    anim->s.f2C = 1.0f;
    ResetAnimeFrameTableInfo(anim->s.table, 0, 0);
    return 1;
}

int GetAnimationDefObjLeaveType(int arg0)
{
    return arg0 != 3;
}

char *GetAnimationDefClass(unsigned char *p)
{
    if (p[0x8] != 0x12) {
        return 0;
    }
    return (char *)p + 0x1C;
}

AnimationDefinition *getAnimationDefByName(unsigned int *reference, const char *name)
{
    int count = resourceCount(reference);
    AnimationDefinition *entry = resourceEntries(reference);
    return findDefinition(entry, count, name);
}

void *CreateAnimationDefObj(void *grp, int size, int **res)
{
    void *o = _isysCreateObj(grp, 0x12, 0x38, *(int *)(*(char **)((char *)*res + 0x20) + 0x14) * 12 + size + 0x43, (int)func_0003FF78, 0x10);

    func_0003F860(res, o, grp);
    return o;
}

static void func_0003FF78(void)
{
}

void InitAnimationDefObj(int arg0, int arg1, int arg2)
{
    func_0003F860(arg2, arg0, arg1);
}
