typedef struct Thread {
    int used;
    int tid;
    struct { char pad0[8]; void *stack; } *info;
    void (*exit)(struct Thread *);
    char pad10[8];
    unsigned int flags;
    struct Thread *prev;
    struct Thread *next;
} Thread;

extern int iosCreateSema(int, int, int);
extern void SleepThread(void);
extern int SignalSema(int);
extern int TerminateThread(int);
extern int DeleteThread(int);
extern short LoaderSysDeleteExternalThreadList(int);
extern void iosFree(void *);
extern void iosJumpRecoverPoint(void *);
extern char RO_00042758[];
extern int B_000516E0[];
extern Thread *B_00051AE0;
extern Thread *B_00051AE4;
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
            t->used = 0;
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
