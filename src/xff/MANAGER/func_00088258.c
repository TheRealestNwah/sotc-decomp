extern int SetLayoutObjAccessSwitchThisObjOnly(void *, int);
extern void SetFogColAvailableFlag(void *, int);

static inline char *GetObjWork(unsigned char *obj, int type)
{
    if (obj[8] == type) {
        return (char *)obj + 0x20;
    }
    return 0;
}

static void func_00088258(unsigned char *obj)
{
    char *anim = GetObjWork(obj, 0xD);
    char *a2;
    int *list;
    int i;
    char *info;

    anim[0x364] = 1;
    anim[0x366] = -1;
    if (SetLayoutObjAccessSwitchThisObjOnly(obj, 0) == 0)
        return;
    a2 = GetObjWork(obj, 0xD);
    list = *(int **)(a2 + 0x328);
    for (i = 0; i < **(int **)(a2 + 0x328); i++) {
        if (((void **)(*(char **)(a2 + 0x338) + i * 8))[0] != 0) {
            SetLayoutObjAccessSwitchThisObjOnly(((void **)(*(char **)(a2 + 0x338) + i * 8))[0], 0);
        } else {
            info = *(char **)(list + 6) + i * 0xC;
            if (*(int *)info == 0x11) {
                if (((void **)(*(char **)(a2 + 0x338) + i * 8))[1] != 0)
                    SetFogColAvailableFlag(((void **)(*(char **)(a2 + 0x338) + i * 8))[1], 0);
            }
        }
    }
}
