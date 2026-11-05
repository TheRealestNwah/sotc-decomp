extern int SetLayoutObjAccessSwitchThisObjOnly(void *, int);
extern void SetFogColAvailableFlag(void *, int);

#ifdef NONMATCHING /* 27 diffs: the 0xD constant is not hoisted into a saved register and the two flag stores swap */
static void func_00088258(unsigned char *obj)
{
    char *anim = obj[8] == 0xD ? (char *)obj + 0x20 : 0;
    char *a2;
    int *list;
    int i;

    anim[0x366] = -1;
    anim[0x364] = 1;
    if (SetLayoutObjAccessSwitchThisObjOnly(obj, 0) == 0)
        return;
    a2 = obj[8] == 0xD ? (char *)obj + 0x20 : 0;
    list = *(int **)(a2 + 0x328);
    for (i = 0; i < **(int **)(a2 + 0x328); i++) {
        void **entry = (void **)(*(char **)(a2 + 0x338) + i * 8);

        if (entry[0] != 0) {
            SetLayoutObjAccessSwitchThisObjOnly(entry[0], 0);
        } else if (*(int *)(*(char **)(list + 6) + i * 0xC) == 0x11) {
            if (entry[1] != 0)
                SetFogColAvailableFlag(entry[1], 0);
        }
    }
}
#endif
