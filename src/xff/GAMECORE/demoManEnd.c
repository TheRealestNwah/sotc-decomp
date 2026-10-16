extern char rootPtn[];
extern void func_000D4768(void);
extern char *GetScriptLayoutClass(void *);
extern void *createScriptObj(void (*)(void), int, void *, int, int, int, int, int);
extern void CancelCaptionSubThreadAll(void);
extern void SetDisplayModelNearClippingSwitch(int);

void demoManEnd(void *o)
{
    char *w = *(char **)(GetScriptLayoutClass(o) + 0x2D8);

    if (*(int *)(w + 0x20) > 0)
        createScriptObj(func_000D4768, *(int *)(w + 0x20), rootPtn, 0x1000, 0, 1, 0, 0);
    if (*(int *)(w + 0x2C) > 0)
        createScriptObj(func_000D4768, *(int *)(w + 0x2C), rootPtn, 0x1000, 0, 1, 0, 0);
    *(int *)(w + 0x10) = 1;
    CancelCaptionSubThreadAll();
    SetDisplayModelNearClippingSwitch(1);
}
