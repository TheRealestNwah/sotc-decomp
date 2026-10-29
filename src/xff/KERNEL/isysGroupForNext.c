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

SysGroup *isysGroupForNext(SysGroup *group)
{
    GroupObj *old = group->obj;
    do {
        group = group->next ? &B_0006D640[group->next] : 0;
    } while (group != 0 && (group->removed != 0 || (group->obj->flags & 1)));
    if (group != 0) {
        old->iterating--;
        group->obj->iterating++;
    }
    return group;
}
