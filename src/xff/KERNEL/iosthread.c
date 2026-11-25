/* Matches only with -fno-strict-aliasing (config/ee_cflags.json), for
   iosCreateThread. */
typedef struct {
    int status;
    void (*func)(void);
    void *stack;
    int stack_size;
    void *gp_reg;
    int initial_priority;
    char pad18[0x18];
} ThreadParam;

typedef struct Thread {
    int id;
    int tid;
    ThreadParam *info;
    void (*exit)(struct Thread *);
    char pad10[4];
    int prio;
    unsigned int flags;
    struct Thread *prev;
    struct Thread *next;
    char pad24[0x8];
} Thread;

extern void *memcpy(void *, const void *, unsigned int);
extern void *memset(void *, int, unsigned int);
extern void WaitSema(int);
extern int SignalSema(int);
extern int CreateThread(ThreadParam *);
extern int StartThread(int, void *);
extern int TerminateThread(int);
extern int DeleteThread(int);
extern void SleepThread(void);
extern int GetThreadId(void);
extern void LoaderSysEntryExternalThreadList(int);
extern short LoaderSysDeleteExternalThreadList(int);
extern void iosJumpRecoverPoint(const char *, ...);
extern int iosCreateSema(int, int, int);
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern int iosSystemSema;
extern int D_000408F4;
extern char RO_000426C8[];
extern char RO_000426F8[];
extern char RO_00042758[];
extern char _gp[];
extern ThreadParam B_00050B60[32];
extern Thread B_00051160[32];
extern Thread *B_000516E0[256];
extern Thread *B_00051AE0;
extern Thread *B_00051AE4;
extern char B_00051AF0[];
extern Thread *B_00053AF0;
extern Thread *B_00053AF4;
extern void (*B_00053AF8)(int);
extern int B_00053AFC;
extern int B_00053B00;
extern int B_00053B04;

static inline void list_remove(Thread **head, Thread *t)
{
    Thread *next = t->next;
    Thread *prev = t->prev;
    if (t == *head) {
        *head = next;
    }
    if (prev != 0) {
        prev->next = next;
    }
    if (next != 0) {
        next->prev = prev;
    }
}

static inline void list_push(Thread **head, Thread *t)
{
    t->prev = 0;
    t->next = *head;
    if (*head != 0) {
        (*head)->prev = t;
    }
    *head = t;
}

static inline Thread *iosAllocThread(void)
{
    register Thread **head __asm__("$3") = &B_00051AE0;
    Thread *t = *head;
    Thread *next;

    if (t != 0) {
        next = t->next;
        *head = next;
        if (next != 0) {
            next->prev = 0;
        }
        list_push(&B_00051AE4, t);
        t->flags &= ~1;
    }
    return t;
}

Thread *iosCreateThread(void (*func)(void), char *stack, int size, int prio, int unused)
{
    Thread *t;
    int id;

    WaitSema(iosSystemSema);
    t = iosAllocThread();
    if (t != 0) {
        if (++D_000408F4 == 0) {
            id = ++D_000408F4;
        } else {
            id = D_000408F4;
        }
        t->id = id;
        t->info->func = func;
        t->info->stack = stack;
        memcpy(stack, "<THREAD_SP>....", 16);
        memcpy(stack + size - 16, "<THREAD_SP_END>", 16);
        t->info->stack_size = size - 16;
        t->info->gp_reg = _gp;
        t->prio = prio;
        t->info->initial_priority = prio;
        t->tid = CreateThread(t->info);
        B_000516E0[t->tid] = t;
        LoaderSysEntryExternalThreadList(t->tid);
    } else {
        iosJumpRecoverPoint(RO_000426C8);
    }
    SignalSema(iosSystemSema);
    return t;
}

static void func_00006340(void)
{
    int *sp = &B_00053B04;
    *sp = iosCreateSema(1, 1, 0);
    while (1) {
        SleepThread();
        switch (B_00053B00) {
        case 0: {
            Thread *t = B_00053AF4;
            int tid;

            if (t->exit != 0) {
                t->exit(t);
            }
            tid = t->tid;
            list_remove(&B_00051AE4, t);
            list_push(&B_00051AE0, t);
            TerminateThread(tid);
            DeleteThread(tid);
            LoaderSysDeleteExternalThreadList(tid);
            if (t->flags & 1) {
                iosFree(t->info->stack);
            }
            t->id = 0;
            B_000516E0[tid] = 0;
            break;
        }
        case 1:
            B_00053AF8(B_00053AFC);
            break;
        default:
            iosJumpRecoverPoint(RO_00042758);
            break;
        }
        SignalSema(B_00053B04);
    }
}

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

Thread *iosGetThread(void)
{
    return B_000516E0[GetThreadId()];
}

Thread *iosCreateThreadS(void *entry, int unused, void *partition, int size, int priority, int flags)
{
    void *stack;
    Thread *thread;
    stack = iosMallocAlign(partition, size, 16);
    thread = 0;
    if (!stack) {
        iosJumpRecoverPoint(RO_000426F8);
    } else {
        thread = iosCreateThread(entry, stack, size, priority, flags);
        if (thread)
            thread->flags |= 1;
        else
            iosFree(stack);
    }
    return thread;
}
