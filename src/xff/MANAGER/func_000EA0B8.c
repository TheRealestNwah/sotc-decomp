typedef struct {
    char pad0[4];
    int (*check)(char *);
} TargetFuncs;

typedef struct {
    char *owner;
    char pad4[0x10];
    TargetFuncs *funcs;
} TargetWork;

extern char *GetCharacterClass(char *);
extern char *GetScriptLayoutClass(char *);
extern char *GetScriptAnimationClass(char *);
extern int func_000E9E50(TargetWork *, char *, char *, char *);

#ifdef NONMATCHING
/* 39 diffs: check result and target pick use branches/registers the original lays out differently */
static int func_000EA0B8(char *obj, TargetWork *w)
{
    char *damage;
    char *target;
    char *p;
    char *l;
    int ok;

    switch (*(unsigned char *)(obj + 8)) {
    case 9:
        damage = GetCharacterClass(obj) + 0x200;
        break;
    case 0xB:
        damage = GetScriptLayoutClass(obj) + 0x230;
        break;
    case 0xD:
        damage = GetScriptAnimationClass(obj) + 0x230;
        break;
    case 0x16:
        damage = obj + 0x290;
        break;
    default:
        damage = 0;
        break;
    }
    if (obj != w->owner && damage != 0) {
        target = 0;
        p = GetCharacterClass(obj);
        if (p != 0) {
            target = p;
            if (*(signed char *)(p + 0x532) == 0)
                target = 0;
        }
        if (target == 0) {
            l = GetScriptLayoutClass(obj);
            if (l != 0 && *(int *)(l + 0x2D0) != 0)
                target = l + 0x70;
        }
        if (target != 0 && func_000E9E50(w, damage, target, obj) != 0) {
            ok = 1;
            if (w->funcs->check != 0) {
                ok = 0;
                if (w->funcs->check(obj) != 0)
                    ok = 1;
            }
            if (ok)
                return 1;
        }
    }
    return 0;
}
#endif
