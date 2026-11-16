typedef struct Hooks { int pad0; int (*check)(void *); } Hooks;
typedef struct Target { void *self; char pad4[0x28]; Hooks *hooks; } Target;
extern signed char *GetCharacterClass(void *);
extern char *GetScriptLayoutClass(void *);
extern char *GetScriptAnimationClass(void *);
extern int func_000EAB40(Target *, void *, void *, void *);

/* Check callback for the damage-box letters SendDamageBoxLetter sends: picks the hit object's damage record by its type, requires a character class with the flag at 0x532 set or an active layout class, tests the box with func_000EAB40, then asks the receiver's optional hook. */
static inline int hookok(Target *t, void *obj) { if (t->hooks->check != 0) { if (t->hooks->check(obj) == 0) return 0; } return 1; }
static int func_000EAED8(unsigned char *obj, Target *t)
{
    char *s0;
    char *s2;
    signed char *p;
    char *q;

    switch (obj[8]) {
    case 9:
        s0 = (char *)GetCharacterClass(obj) + 0x200;
        break;
    case 0xB:
        s0 = GetScriptLayoutClass(obj) + 0x230;
        break;
    case 0xD:
        s0 = GetScriptAnimationClass(obj) + 0x230;
        break;
    case 0x16:
        s0 = (char *)obj + 0x290;
        break;
    default:
        s0 = 0;
        break;
    }
    if (obj != t->self && s0 != 0) {
        p = GetCharacterClass(obj);
        s2 = 0;
        if (p != 0 && p[0x532] != 0)
            s2 = (char *)p;
        if (s2 == 0) {
            q = GetScriptLayoutClass(obj);
            if (q != 0)
                s2 = *(int *)(q + 0x2D0) ? q + 0x70 : s2;
        }
        if (s2 != 0 && func_000EAB40(t, s0, s2, obj) != 0) {
            if (hookok(t, obj))
                return 1;
        }
    }
    return 0;
}
