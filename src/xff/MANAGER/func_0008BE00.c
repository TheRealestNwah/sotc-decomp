#ifdef NONMATCHING
/* Parked: 3 words differ. Laying the direct-resource call inline and using a fresh i = idx + 1 fixes the block order and registers (was 15); the original still uses bc1t with a duplicated mov.s f13 in the bc1f delay slot where gcc picks bc1tl. */
extern int DldSysUndefSymbol;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; char padC[4]; char *data; } DldTable;
static inline void *dldElement(int *h)
{
    int off = *h & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && t != (DldTable *)DldSysUndefSymbol) ? t->data + (((unsigned int)*h >> 18) & 0xFFF) * t->type->size : 0;
}
extern void GetAnimationClassCurrentInfoDirectResource(void *, void *, float, float);
extern void GetAnimationClassCurrentInfoWithOutsideLimit(void *, int, float, float);
extern void ResetAnimeFrameTableInfo(void *, void *, int);
extern void ExecAnimeTableInfo(void *, void *, float);

static inline char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return (char *)obj + 0x20;
    }
    return 0;
}

static void func_0008BE00(unsigned char *obj, float rate, float delta)
{
    char *w = GetObjWork(obj, 0xD);
    int idx = *(signed char *)(w + 0x366);
    char *anim = w + 0x2E0;
    int *list = *(int **)(w + 0x328);
    char *res = *(char **)(w + 0x334);
    int cnt;

    if (idx < 0)
        goto direct;
    {
        float f = -1.0f;
        int i = idx + 1;
        if (i < list[2])
            f = ((float *)list[3])[i];
        if (f < 0.0f || (float)(*(short *)(res + 4) - 1) <= f) {
        direct:
            GetAnimationClassCurrentInfoDirectResource(anim, res, rate, delta);
        } else {
            GetAnimationClassCurrentInfoWithOutsideLimit(anim, (int)f, rate, delta);
        }
    }
    if (*(int *)(anim + 0x20) != 0)
        ResetAnimeFrameTableInfo(anim + 0x30, dldElement((int *)(*(char **)(w + 0x32C) + 0xC)), 0);
    else
        ExecAnimeTableInfo(anim + 0x30, obj, *(float *)(anim + 8) * *(float *)(anim + 0x2C));
    cnt = *(int *)(w + 0x340);
    if (cnt != -1)
        *(int *)(w + 0x340) = cnt + 1;
}
#endif
