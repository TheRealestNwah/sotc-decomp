extern int DldSysUndefSymbol;
extern int _SkelFocusDef;
extern int _LayoutObjDef;
extern int GetSkeletonFocusNode(unsigned int *);
extern int GetCharacterClass(void *);
extern int GetScriptAnimationClass(void *);
extern void *GetScriptAnimationObjChildObjWithName(void *, int);
extern void *GetLayoutObjChildWithName(void *, int);

static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static inline char *dldClass(unsigned int *h)
{
    int off = *h & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;

    return (t != 0 && t != (char *)DldSysUndefSymbol) ? t : 0;
}

static void *func_0001B9A8(int *out, void *obj, unsigned int *node)
{
    char *e = dldResolve(node);
    int r = 0;

    if (e != 0) {
        if (*(int **)(dldClass(node) + 8) == &_SkelFocusDef) {
            r = GetSkeletonFocusNode(node);
            if (GetCharacterClass(obj) == 0 && r < 0)
                r = 0;
        } else if (*(int **)(dldClass(node) + 8) == &_LayoutObjDef) {
            int name = *(int *)e;

            if (GetScriptAnimationClass(obj)) {
                r = 0;
                obj = GetScriptAnimationObjChildObjWithName(obj, name);
            } else {
                r = 0;
                obj = GetLayoutObjChildWithName(obj, name);
            }
        } else {
            r = 0;
        }
    }
    *out = r;
    return obj;
}

