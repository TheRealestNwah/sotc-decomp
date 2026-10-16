typedef struct {
    char pad0[0x1AC];
    int pause;
} GlobalVar;

extern GlobalVar gcGlobalVar;
extern void *isysGetThisSubThread(void);
extern char *GetLayoutClass(void *);
extern void *GetGeometryPointerObject(void *);
extern int _omakeSelectFlagChk(int);
extern void SetLayoutObjAccessSwitch(void *, int);
extern void nico_weaponUpdateGeometry(char *);
extern void FlushCollisionWork(void *);
extern void scrRun(void);

void nico_weaponstart(void)
{
    void *th = isysGetThisSubThread();
    char *c = GetLayoutClass(th);
    GlobalVar *g = &gcGlobalVar;

    for (;;) {
        char *pc = *(int *)(c + 0x124) != 0 ? GetLayoutClass(GetGeometryPointerObject(c + 0xC0)) : 0;

        if ((pc != 0 && (*(long *)(*(char **)(pc + 0x144) + 0x260) & 0x30)) || _omakeSelectFlagChk(7))
            SetLayoutObjAccessSwitch(th, 0);
        else
            SetLayoutObjAccessSwitch(th, 1);
        if (g->pause == 0) {
            nico_weaponUpdateGeometry(c);
            FlushCollisionWork(th);
        }
        scrRun();
    }
}
