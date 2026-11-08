typedef struct {
    char pad[0x30];
} ThreadInfo;

typedef struct Thread {
    int used;
    int tid;
    ThreadInfo *info;
    char pad0C[0x10];
    struct Thread *prev;
    struct Thread *next;
    char pad24[0x8];
} Thread;

extern void *memset(void *, int, unsigned int);
extern int GetThreadId(void);
extern int StartThread(int, void *);
extern Thread *iosCreateThread(void (*)(void), void *, int, int, int);
extern void func_00006340(void);
extern ThreadInfo B_00050B60[32];
extern Thread B_00051160[32];
extern Thread *B_000516E0[256];
extern Thread *B_00051AE0;
extern int B_00051AE4;
extern char B_00051AF0[];
extern Thread *B_00053AF0;

void iosInitThreadSystem(void)
{
    int i;
    Thread *t;

    memset(B_000516E0, 0, sizeof(B_000516E0));
    memset(B_00051160, 0, sizeof(B_00051160));
    for (i = 0; i < 32; i++)
        B_00051160[i].info = &B_00050B60[i];
    B_00051AE0 = B_00051160;
    B_00051AE4 = 0;
    for (i = 0; i < 31; i++)
        B_00051160[i].next = &B_00051160[i + 1];
    B_00051160[31].next = 0;
    B_00051160[0].prev = 0;
    for (i = 1; i < 32; i++)
        B_00051160[i].prev = &B_00051160[i - 1];
    B_00053AF0 = iosCreateThread(func_00006340, B_00051AF0, 0x2000, 2, 0);
    t = B_00053AF0;
    if (t == 0)
        t = B_000516E0[GetThreadId()];
    StartThread(t->tid, 0);
}
