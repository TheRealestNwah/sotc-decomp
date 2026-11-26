typedef struct {
    void (*func)(void);
    int count;
} Ctrl;

extern Ctrl B_000C5A80[];
extern int B_000C5B00;
extern int B_000C5B04;
extern void Sg2RemoteSend(int, int, int, int);
extern int DIntr(void);
extern int EIntr(void);

int Sg2CtrlEntryTickProcById(int i, void (*proc)(void));
int Sg2CtrlSetTickTime(int arg0);

int Sg2ChipInitHot(void)
{
    Sg2RemoteSend(0x11, 1, 0, 0);
    return 0;
}

static void func_0001F6C8(void)
{
}

int Sg2CtrlEntryTickProc(void (*proc)(void))
{
    int result = -1;
    int enabled = DIntr();
    int i;
    for (i = 0; i < 16; ++i) {
        if (B_000C5A80[i].func == func_0001F6C8) {
            Sg2CtrlEntryTickProcById(i, proc);
            result = 0;
            break;
        }
    }
    if (enabled)
        EIntr();
    return result;
}

int Sg2CtrlEntryTickProcById(int i, void (*proc)(void))
{
    if (B_000C5A80[i].func != func_0001F6C8)
        return -1;
    B_000C5A80[i].func = proc;
    B_000C5A80[i].count = 0;
    return i;
}

int Sg2CtrlRemoveTickProc(void (*proc)(void))
{
    int result = -1;
    int enabled = DIntr();
    int i;
    for (i = 0; i < 16; ++i) {
        if (B_000C5A80[i].func == proc) {
            B_000C5A80[i].func = func_0001F6C8;
            B_000C5A80[i].count = 0;
            result = 0;
            break;
        }
    }
    if (enabled)
        EIntr();
    return result;
}

void Sg2CtrlTickProc(void)
{
    int i;
    Ctrl *c = B_000C5A80;
    (*(volatile int *)&B_000C5B00)++;
    for (i = 15; i >= 0; i--, c++) {
        c->func();
        c->count++;
    }
}

int Sg2CtrlSetTickMode(int arg0)
{
    int temp_v0;

    temp_v0 = B_000C5B04;
    B_000C5B04 = arg0;
    return temp_v0;
}

int Sg2CtrlGetTickMode(void)
{
    return B_000C5B04;
}

int Sg2CtrlSetTickTime(int arg0)
{
    int temp_v0;

    temp_v0 = B_000C5B00;
    B_000C5B00 = arg0;
    return temp_v0;
}

int Sg2CtrlGetTickTime(void)
{
    return B_000C5B00;
}

int Sg2CtrlInit(int reserved)
{
    int i;
    for (i = 0; i < 16; i++) {
        B_000C5A80[i].func = func_0001F6C8;
        B_000C5A80[i].count = 0;
    }
    Sg2CtrlSetTickTime(0);
    return 0;
}
