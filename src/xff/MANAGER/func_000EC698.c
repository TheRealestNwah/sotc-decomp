extern int DldSysUndefSymbol;
extern char *ControlDef_ELSE_ALWAYS;
extern char _ControlDef[];
extern char *D_00139F78;
extern char *D_00139F7C;
extern char *D_00139F80;
extern char *GetLayoutClass(char *);
extern void GetControlCheckStatusFromGP(void *, char *);
extern int CheckControlDefByStatus(void *, void *);
extern int CheckControlDef(char *, char *, char *, void *);
extern int execCondition(char *, void *);
extern int func_000ED618(void *, void *);

static inline char *dldModule(unsigned int *reference)
{
    unsigned int offset = *reference & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol)
        return module;
    return 0;
}

static inline char *dldEntry(unsigned int *reference)
{
    unsigned int encoded = *reference;
    unsigned int offset = encoded & 0x3FFFF;
    char *module;

    if (offset)
        module = *(char **)((char *)reference - offset);
    else
        module = 0;
    if (module && module != (char *)DldSysUndefSymbol) {
        int index = (encoded >> 18) & 0xFFF;
        char *definition = *(char **)(module + 8);
        char *data = *(char **)(module + 0x10);
        return data + index * *(int *)(definition + 0xC);
    }
    return 0;
}

typedef struct {
    unsigned int ref;
    int data;
} Entry;

/* Parked: 7 diffs (28 before permuter runs; passing the entry as CheckControlDef's fourth
 * argument took it from 13 to 10, and deriving ent from q took it to 7). Remaining: the
 * D_00139F7C walk sets up its loop constants (lui s5/s4, addiu s0, daddu s2) in a different
 * order, and the Original recomputes ent as first + i (addu a3) at the top of the body,
 * with the loop test using its own a0 = i + first, where gcc derives ent from q. Computing
 * ent as first + i gets CSE'd with the loop test (10 diffs). */
#ifdef NONMATCHING
static int func_000EC698(unsigned int *list, void *ctx)
{
    Entry *first = (Entry *)dldEntry(list);
    char *elseAlways = ControlDef_ELSE_ALWAYS;
    char *e;
    char *def;
    int r;
    int failed;
    int i;
    int j = 0;

    if (D_00139F7C) {
        char *q = (char *)first + 4;
        for (i = 0; (e = dldEntry((unsigned int *)((char *)first + i))) != 0; q += 8, i += 8) {
            if (e != elseAlways) {
                Entry *ent = (Entry *)(q - 4);
                if (*(char **)(dldModule(&ent->ref) + 8) == _ControlDef) {
                    def = D_00139F7C;
                    if (CheckControlDef(D_00139F78, D_00139F7C, def + 0x760, ent) <= 0)
                        continue;
                } else {
                    failed = !execCondition(D_00139F78, ent);
                    if (failed)
                        continue;
                }
            }
            r = func_000ED618(q, ctx);
            if (r)
                return r;
        }
        return 0;
    } else {
        int status[8];
        char *lgp = 0;
        char *gp;
        char *lc;

        if (D_00139F78) {
            lc = GetLayoutClass(D_00139F78);
            if (lc && *(int *)(lc + 0x124))
                lgp = lc + 0xC0;
        }
        if (!lgp)
            gp = D_00139F80;
        else
            gp = lgp;
        if (gp)
            GetControlCheckStatusFromGP(status, gp);
        for (; (e = dldEntry(&first[j].ref)) != 0; j++) {
            if (e != elseAlways) {
                if (!gp)
                    continue;
                if (CheckControlDefByStatus(status, &first[j]) <= 0)
                    continue;
            }
            r = func_000ED618(&first[j].data, ctx);
            if (r)
                return r;
        }
        return 0;
    }
}
#endif
