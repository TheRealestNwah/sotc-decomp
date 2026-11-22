extern int *DldSysUndefSymbol;
extern int ControlDef_ELSE_ALWAYS;
extern int D_00139F78;
extern int D_00139F7C;
extern int D_00139F80;
extern char *GetLayoutClass(int);
extern int CheckControlDef(void *, void *, void *, unsigned int *);
extern void GetControlCheckStatusFromGP(void *, void *);
extern int CheckControlDefByStatus(void *, unsigned int *);

static inline int dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    if (t != 0 && t != DldSysUndefSymbol)
        return t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3];
    return 0;
}

typedef struct {
    unsigned int ref;
    int data;
} CtrlEntry;

static int *func_000ED160(unsigned int *ref)
{
    CtrlEntry *arr = (CtrlEntry *)dldResolve(ref);
    int elseAlways = ControlDef_ELSE_ALWAYS;
    int j = 0;
    int def;
    char *lc;
    void *lgp;
    void *gp;
    int status[8];

    if (D_00139F7C != 0) {
        int i = 0;
        for (; (def = dldResolve(&arr[i].ref)) != 0; i++) {
            if (def != elseAlways) {
                if (CheckControlDef((void *)D_00139F78, (void *)D_00139F7C, (char *)D_00139F7C + 0x760, &arr[i].ref) <= 0)
                    continue;
            }
            return &arr[i].data;
        }
        return 0;
    }
    lgp = 0;
    if (D_00139F78 != 0) {
        lc = GetLayoutClass(D_00139F78);
        if (lc != 0 && *(int *)(lc + 0x124) != 0)
            lgp = lc + 0xC0;
    }
    if (!lgp)
        gp = (void *)D_00139F80;
    else
        gp = lgp;
    if (gp != 0)
        GetControlCheckStatusFromGP(status, gp);
    for (; (def = dldResolve(&arr[j].ref)) != 0; j++) {
        if (def != elseAlways) {
            if (!gp)
                continue;
            if (CheckControlDefByStatus(status, &arr[j].ref) <= 0)
                continue;
        }
        return &arr[j].data;
    }
    return 0;
}
