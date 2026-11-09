typedef struct {
    void *obj;
    int unk4;
    char pad8[4];
    unsigned char removed;
    char padD;
    unsigned short next;
    char pad10[6];
    short freeNext;
} SysGroup;

typedef struct {
    unsigned short first;
    short count;
} GroupHead;

extern int GetThreadId();
extern void SignalSema(int);
extern void WaitSema(int);
extern int B_000BF6CC;
extern SysGroup *B_000BF6C4;
extern int D_00040D5C;
extern int D_00040D60;
extern SysGroup B_0006D640[];

/* Parked: 2 diffs: count store scheduled after D_00040D60 load */
#ifdef NONMATCHING
void isysDeleteGroupAllObj(GroupHead *head)
{
    SysGroup *g;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    g = head->first ? &B_0006D640[head->first] : 0;
    while (g != 0) {
        if (g->removed != 1) {
            g->removed = 1;
            g->freeNext = B_000BF6C4 ? B_000BF6C4 - B_0006D640 : 0;
            B_000BF6C4 = g;
        }
        g->unk4 = 0;
        g = g->next ? &B_0006D640[g->next] : 0;
    }
    head->count = 0;
    head->first = 0;
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}
#else
extern void isysDeleteGroupAllObj(GroupHead *head);
#endif
