typedef struct {
    int status;
    void (*func)(void);
    void *stack;
    int stack_size;
    void *gp_reg;
    int initial_priority;
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
} Thread;

extern void WaitSema(int);
extern void SignalSema(int);
extern int CreateThread(ThreadParam *);
extern void LoaderSysEntryExternalThreadList(int);
extern void iosJumpRecoverPoint(const char *);
extern void *memcpy(void *, const void *, unsigned int);
extern int iosSystemSema;
extern Thread *B_00051AE0;
extern Thread *B_00051AE4;
extern Thread *B_000516E0[];
extern int D_000408F4;
extern char RO_000426C8[];
extern char _gp[];

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
    Thread *t = B_00051AE0;
    Thread *next;

    if (t != 0) {
        next = t->next;
        B_00051AE0 = next;
        if (next != 0) {
            next->prev = 0;
        }
        list_push(&B_00051AE4, t);
        t->flags &= ~1;
    }
    return t;
}

/* Parked: Parked: ~65-84 words differ (inlined thread pop/push register allocation and counter base) */
#ifdef NONMATCHING
Thread *iosCreateThread(void (*func)(void), char *stack, int size, int prio)
{
    Thread *t;
    int id;

    WaitSema(iosSystemSema);
    t = iosAllocThread();
    if (t != 0) {
        if (++D_000408F4 == 0) {
            ++D_000408F4;
        }
        t->id = D_000408F4;
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
#else
extern Thread *iosCreateThread(void (*func)(void), char *stack, int size, int prio);
#endif
