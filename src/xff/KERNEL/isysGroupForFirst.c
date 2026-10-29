typedef struct {
    char pad0[9];
    unsigned char iterating;
    short flags;
} GroupObj;

typedef struct {
    GroupObj *obj;
    char pad4[8];
    unsigned char removed;
    char padD;
    unsigned short next;
    char pad10[8];
} SysGroup;

typedef struct {
    unsigned short first;
} GroupHead;

extern int GetThreadId();
extern void SignalSema(int);
extern void WaitSema(int);
extern int B_000BF6CC;
extern int D_00040D5C;
extern int D_00040D60;
extern SysGroup B_0006D640[];

SysGroup *isysGroupForFirst(GroupHead *head, int reserved)
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
        if (g->removed == 0 && !(g->obj->flags & 1)) {
            g->obj->iterating++;
            break;
        }
        g = g->next ? &B_0006D640[g->next] : 0;
    }
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
    return g;
}
