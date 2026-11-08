extern int SetLayoutObjAccessSwitchThisObjOnly(void *, int);
extern void SetFogColAvailableFlag(void *, int);
extern char *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(void *);

static inline char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return (char *)obj + 0x20;
    }
    return 0;
}

static inline void setsw(unsigned char *obj, int sw)
{
    char *a2;
    int *list;
    int i;
    char *info;

    if (SetLayoutObjAccessSwitchThisObjOnly(obj, sw) == 0)
        return;
    a2 = GetObjWork(obj, 0xD);
    list = *(int **)(a2 + 0x328);
    for (i = 0; i < **(int **)(a2 + 0x328); i++) {
        if (((void **)(*(char **)(a2 + 0x338) + i * 8))[0] != 0) {
            SetLayoutObjAccessSwitchThisObjOnly(((void **)(*(char **)(a2 + 0x338) + i * 8))[0], sw);
        } else {
            info = *(char **)(list + 6) + i * 0xC;
            if (*(int *)info == 0x11) {
                if (((void **)(*(char **)(a2 + 0x338) + i * 8))[1] != 0)
                    SetFogColAvailableFlag(((void **)(*(char **)(a2 + 0x338) + i * 8))[1], sw);
            }
        }
    }
}

static void func_00088678(unsigned char *obj, int sw)
{
    char *cls = GetLayoutClass(obj);
    void *p;

    if (*(int *)(cls + 0x124) != 0)
        p = GetGeometryPointerObject(cls + 0xC0);
    else
        p = 0;
    if (p != 0)
        setsw(obj, *(signed char *)(GetLayoutClass(p) + 0x1B8));
    else
        setsw(obj, sw);
}
