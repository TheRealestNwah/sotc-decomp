typedef struct {
    short pad0;
    unsigned short first;
} GroupHead;

typedef struct {
    void *obj;
    GroupHead *group;
    int arg;
    unsigned char removed;
    char padD;
    unsigned short next;
    char pad10[2];
    unsigned short objNext;
    unsigned short objPrev;
    short freeNext;
} SysGroup;

typedef struct {
    char pad0[0xC];
    unsigned short groups;
    unsigned short last;
} GroupObj;

extern int GetThreadId();
extern void SignalSema(int);
extern void WaitSema(int);
extern int B_000BF6CC;
extern SysGroup *B_000BF6C0;
extern int D_00040D5C;
extern int D_00040D60;
extern SysGroup B_0006D640[];
extern char RO_00044348[];
extern void iosJumpRecoverPoint(char *, ...);
extern void func_00019820(SysGroup *, SysGroup *, int);

int isysAddGroupRelativeWithLinkParam(GroupObj *obj, GroupHead *group, SysGroup *rel, int mode, int unused, int param)
{
    SysGroup *g;
    SysGroup *p;
    SysGroup *q;
    int tid = GetThreadId();

    if (tid == D_00040D5C) {
        D_00040D60 += 1;
    } else {
        WaitSema(B_000BF6CC);
        D_00040D5C = tid;
        D_00040D60 = 1;
    }
    g = B_000BF6C0;
    if (g != 0) {
        B_000BF6C0 = g->next ? &B_0006D640[g->next] : 0;
    }
    g->arg = param;
    g->obj = obj;
    g->group = group;
    if (group == 0 || obj == 0) {
        iosJumpRecoverPoint(RO_00044348, group, obj);
    }
    func_00019820(rel, g, mode);
    q = g;
    if (obj->groups == 0) {
        q->objPrev = 0;
        obj->groups = q ? q - B_0006D640 : 0;
    } else {
        q->objPrev = obj->last;
        p = obj->last ? &B_0006D640[obj->last] : 0;
        p->objNext = q ? q - B_0006D640 : 0;
    }
    q->objNext = 0;
    obj->last = q ? q - B_0006D640 : 0;
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
    return q != 0;
}
