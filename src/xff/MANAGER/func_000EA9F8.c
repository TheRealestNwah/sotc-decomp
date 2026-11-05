#ifdef NONMATCHING /* 25 diffs: the early returns load the result register differently and the final filter test is not branched */
extern char *GetCharacterClass(void *);
extern char *GetScriptLayoutClass(void *);
extern char *GetScriptAnimationClass(void *);
extern int func_000EA6F0(void *, char *, char *, char *);

static inline char *getDamageClass(char *o)
{
    switch (((unsigned char *)o)[8]) {
    case 9:
        return GetCharacterClass(o) + 0x200;
    case 0xB:
        return GetScriptLayoutClass(o) + 0x230;
    case 0xD:
        return GetScriptAnimationClass(o) + 0x230;
    case 0x16:
        return o + 0x290;
    }
    return 0;
}

static inline int body(char *o, char **p)
{
    char *dmg = getDamageClass(o);
    char *cls;
    int (*fn)(char *);

    if (o == p[0])
        return 0;
    if (dmg == 0)
        return 0;
    cls = GetCharacterClass(o);
    if (cls == 0) {
        char *layout = GetScriptLayoutClass(o);

        if (layout != 0 && *(int *)(layout + 0x2D0) != 0)
            cls = layout + 0x70;
    }
    if (cls == 0)
        return 0;
    if (func_000EA6F0(p, dmg, cls, o) == 0)
        return 0;
    fn = *(int (**)(char *))(p[0xD] + 4);
    {
        int ok = fn == 0 || fn(o) != 0;

        if (ok)
            return 1;
    }
    return 0;
}

static int func_000EA9F8(char *o, char **p)
{
    return body(o, p);
}
#endif
