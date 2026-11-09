typedef struct {
    void *obj;
    int unk4;
    int arg;
    unsigned char removed;
    char padD[5];
    unsigned short objNext;
    short pad14;
    short freeNext;
} SysGroup;

typedef struct {
    char pad0[0xC];
    unsigned short groups;
} GroupObj;

extern int GetThreadId();
extern void SignalSema(int);
extern void WaitSema(int);
extern int B_000BF6CC;
extern SysGroup *B_000BF6C4;
extern int D_00040D5C;
extern int D_00040D60;
extern SysGroup B_0006D640[];
extern char RO_00044378[];
extern void iosJumpRecoverPoint(char *);

void isysDeleteGroupWithLinkParam(GroupObj *obj, int group, int param, int noError)
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
    for (g = obj->groups ? &B_0006D640[obj->groups] : 0; g != 0;
         g = g->objNext ? &B_0006D640[g->objNext] : 0) {
        if (g->unk4 == group && g->arg != 0) {
            goto found;
        }
    }
    if (noError != 0) {
        goto end;
    }
    iosJumpRecoverPoint(RO_00044378);
found:
    if (g->removed != 1) {
        g->removed = 1;
        g->freeNext = B_000BF6C4 ? B_000BF6C4 - B_0006D640 : 0;
        B_000BF6C4 = g;
    }
end:
    if (--D_00040D60 == 0) {
        D_00040D5C = -1;
        SignalSema(B_000BF6CC);
    }
}
