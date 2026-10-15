typedef struct { void *proc; int arg; } Sg2Tick;
extern Sg2Tick B_000C5A80[];
extern void func_0001F6C8();

int Sg2CtrlEntryTickProcById(int i, void *proc)
{
    if (B_000C5A80[i].proc != func_0001F6C8)
        return -1;
    B_000C5A80[i].proc = proc;
    B_000C5A80[i].arg = 0;
    return i;
}
