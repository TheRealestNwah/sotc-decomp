typedef struct { char pad0[0x20]; void *res; } ColInfo;
typedef struct { char pad0[0x184]; ColInfo *col; } LayoutClass;

extern char *GetSCRCharaAIWorkPtr(void);
extern void *GetScriptAnimationObjChildObjWithName(void *, const char *);
extern LayoutClass *GetLayoutClass(void *);
extern void ChangeCollisionResourceAttribute(void *, int, int, int, int, int, int);

static void func_0006BF40(void)
{
    void *obj = *(void **)(GetSCRCharaAIWorkPtr() + 0x41E4);

    if (obj) {
        LayoutClass *l = GetLayoutClass(GetScriptAnimationObjChildObjWithName(obj, "minotaur_C_weapon"));

        ChangeCollisionResourceAttribute(l->col->res, 1, 1, 1, 1, 1, 0);
    }
}
