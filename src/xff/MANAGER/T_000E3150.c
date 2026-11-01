typedef struct Item {
    char pad[0x2C];
    struct Item *next;
} Item;

typedef struct {
    Item *head;
    Item *tail;
} Queue;

extern int B_0015D4AC;
extern int D_00139F1C;
extern int B_00155498;
extern Item *D_00139F24;
extern int B_00151860;
extern Queue B_00155470[5];
extern int iosGetISchedulerExecCnt(void);
extern void iosWakeupThread(int);
extern void WaitSema(int);
extern void SignalSema(int);

static inline Item *pop(Queue *q)
{
    Item *v = q->head;

    if (v != 0) {
        q->head = v->next;
        if (q->head == 0) {
            q->tail = 0;
        }
    }
    return v;
}

static inline Item *popAny(void)
{
    int i;

    for (i = 0; i < 5; i++) {
        Item *r = pop(&B_00155470[i]);

        if (r != 0) {
            return r;
        }
    }
    return 0;
}

static void T_000E3150(void)
{
    B_0015D4AC = iosGetISchedulerExecCnt();
    if (D_00139F1C != 0) {
        D_00139F1C = 0;
        iosWakeupThread(B_00155498);
    }
    if (D_00139F24 == 0) {
        Item *r;

        WaitSema(B_00151860);
        r = popAny();
        D_00139F24 = r;
        if (r != 0) {
            iosWakeupThread(B_00155498);
        }
        SignalSema(B_00151860);
    }
}
