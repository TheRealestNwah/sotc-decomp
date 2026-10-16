typedef int qword __attribute__((mode(TI)));

typedef struct {
    qword pos;
    int flag;
} RockWork;

extern char rootPtn[];
extern void *isysGetThisSubThread(void);
extern int iosCreatePartition(void *, int);
extern char *GetScrLwsOriClass(void *);
extern void CharaCtrlResetCtrlStatus(void *);
extern void CharaCtrlResetAllScriptCtrlStatus(void *);
extern char *_SCRMallocAlign(int, int, int);
extern char *GetLayoutClass(void *);
extern void scrRunM(int);

void fallenRockStart(void)
{
    void *th = isysGetThisSubThread();
    int part = iosCreatePartition(rootPtn, 0x53);
    char *c;
    RockWork *w;
    char *l;

    *(int *)(GetScrLwsOriClass(th) + 0x1204) = part;
    CharaCtrlResetCtrlStatus(th);
    CharaCtrlResetAllScriptCtrlStatus(th);
    c = GetScrLwsOriClass(th);
    w = (RockWork *)_SCRMallocAlign(part, 0x20, 0x10);
    *(RockWork **)(c + 0x1208) = w;
    w->flag = 0;
    scrRunM(2);
    w->pos = **(qword **)(GetLayoutClass(th) + 0x134);
    l = GetLayoutClass(isysGetThisSubThread());
    for (;;) {
        if (w->flag != 0)
            **(qword **)(l + 0x134) = w->pos;
        scrRunM(1);
    }
}
