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

extern SysGroup B_0006D640[];

SysGroup *isysGroupForNextForce(SysGroup *group)
{
    GroupObj *old = group->obj;
    /* Single-pass do/while keeps the loop-end nop that isysGroupForNext's
       filtering loop leaves behind. */
    do {
        group = group->next ? &B_0006D640[group->next] : 0;
    } while (0);
    if (group != 0) {
        old->iterating--;
        group->obj->iterating++;
    }
    return group;
}
