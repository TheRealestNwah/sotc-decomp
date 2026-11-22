/* Parked: 22 diffs. For every motion-shift entry of the character class (relocatable table at class+0x10EC), resolves the kind and target refs; a non-ALWAYS entry whose target matches looks up the active motion slot and hands it to func_00053058 (returning when that fires). If nothing was found, every ALWAYS entry for the target goes to func_00052EA8. Remaining: the first ref decode goes through v0 instead of a0 with the found=0 store scheduled later, v0/v1 swapped for the decoded target compare, and findSlot keeps the count in a0 instead of copying it from v0. */
#ifdef NONMATCHING
extern int DldSysUndefSymbol;
extern int MotionKind_ALWAYS;
typedef struct { char pad0[0xC]; int size; } DldType;
typedef struct { char pad0[8]; DldType *type; int count; char *data; } DldTable;

static inline DldTable *dldTable(unsigned int *h)
{
    unsigned int off = *h & 0x3FFFF;
    return off != 0 ? *(DldTable **)((char *)h - off) : 0;
}

static inline int dldElement(unsigned int *h)
{
    unsigned int ref = *h;
    unsigned int off = ref & 0x3FFFF;
    DldTable *t = off != 0 ? *(DldTable **)((char *)h - off) : 0;
    return (t != 0 && (int)t != DldSysUndefSymbol) ? (int)t->data + ((ref >> 18) & 0xFFF) * t->type->size : 0;
}

typedef struct {
    unsigned int kind;
    unsigned int target;
    char pad8[0x14];
} Shift;

typedef struct {
    char pad0[4];
    int elem;
    char pad8[0x3C];
    int state;
    char pad48[0x38];
} Slot;

static inline int findSlot(Slot *p, int n, int e)
{
    int i;
    for (i = 0; i < n; i++, p++) {
        if (p->state != -2 && p->elem == e)
            return i;
    }
    return -1;
}

extern char *GetCharacterClass(int);
extern int func_00053058(int, int, Shift *, int, float);
extern void func_00052EA8(int, char *, Shift *, float);

void func_000532C8(int obj, int target, float f)
{
    volatile int vtarget;
    volatile int found;
    char *cls;
    unsigned int *h;
    DldTable *t;
    int n;
    Shift *tab;
    Shift *s;
    int i;
    int always;

    vtarget = target;
    cls = GetCharacterClass(obj);
    h = *(unsigned int **)(cls + 0x10EC);
    always = MotionKind_ALWAYS;
    t = dldTable(h);
    found = 0;
    n = (t != 0 && (int)t != DldSysUndefSymbol) ? t->count : 0;
    t = dldTable(h);
    tab = (t != 0 && (int)t != DldSysUndefSymbol) ? (Shift *)t->data : 0;
    s = tab;
    for (i = 0; i < n; i++, s++) {
        int kind = dldElement(&s->kind);
        if (kind != always && vtarget == dldElement(&s->target)) {
            int j = findSlot(*(Slot **)(cls + 0x30C), *(int *)(cls + 0x3FC), kind);
            if (j >= 0) {
                found = 1;
                if (func_00053058(obj, j, s, kind, f) != 0)
                    return;
            }
        }
    }
    if (found == 0) {
        s = tab;
        if (n > 0) {
            i = n;
            do {
                if (dldElement(&s->kind) == always && vtarget == dldElement(&s->target))
                    func_00052EA8(obj, cls, s, f);
                i--;
                s++;
            } while (i != 0);
        }
    }
}
#endif
