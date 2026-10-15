typedef struct { void *f; int b; } Ctrl;
extern Ctrl B_000C5A80[];
extern void func_0001F6C8();
extern void Sg2CtrlSetTickTime(int);

int Sg2CtrlInit(void)
{
    int i;
    for (i = 0; i < 16; i++) {
        B_000C5A80[i].f = func_0001F6C8;
        B_000C5A80[i].b = 0;
    }
    Sg2CtrlSetTickTime(0);
    return 0;
}
