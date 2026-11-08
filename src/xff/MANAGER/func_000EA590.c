/* Draft: the switch matches; the class lookups and the final result use other registers and branches. */
#ifdef NONMATCHING
typedef struct Obj {
    char pad0[8];
    unsigned char kind;
} Obj;

typedef struct Ops {
    int pad0;
    int (*check)(Obj *);
} Ops;

typedef struct Ctx {
    Obj *self;
    char pad4[0x24];
    Ops *ops;
} Ctx;

extern char *GetCharacterClass(Obj *);
extern char *GetScriptLayoutClass(Obj *);
extern char *GetScriptAnimationClass(Obj *);
extern int func_000EA218(Ctx *, char *, char *, Obj *);

static int func_000EA590(Obj *obj, Ctx *ctx)
{
    char *res;
    char *cls;
    char *c;
    int ok;

    switch (obj->kind) {
    case 9:
        res = GetCharacterClass(obj) + 0x200;
        break;
    case 0xB:
        res = GetScriptLayoutClass(obj) + 0x230;
        break;
    case 0xD:
        res = GetScriptAnimationClass(obj) + 0x230;
        break;
    case 0x16:
        res = (char *)obj + 0x290;
        break;
    default:
        res = 0;
        break;
    }
    if (obj != ctx->self && res != 0) {
        cls = 0;
        c = GetCharacterClass(obj);
        if (c != 0) {
            cls = c[0x532] ? c : 0;
        }
        if (cls == 0) {
            c = GetScriptLayoutClass(obj);
            if (c != 0) {
                cls = *(int *)(c + 0x2D0) ? c + 0x70 : cls;
            }
        }
        if (cls != 0 && func_000EA218(ctx, res, cls, obj) != 0) {
            ok = 1;
            if (ctx->ops->check != 0) {
                ok = ctx->ops->check(obj) != 0;
            }
            if (ok) {
                return 1;
            }
        }
    }
    return 0;
}
#endif
