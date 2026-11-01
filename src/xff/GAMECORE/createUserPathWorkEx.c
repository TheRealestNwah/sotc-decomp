typedef struct UserPathWork {
    char pad0000[0x3C60];
    int path[6];
    int field3C78;
    int field3C7C;
    int field3C80;
    int field3C84;
    int link[3];
    int field3C94;
    char pad3C98[8];
    int field3CA0;
    int field3CA4;
    int field3CA8;
    int field3CAC;
    int field3CB0;
} UserPathWork;

extern void func_000FC0C0(UserPathWork *);
extern void createUserPathWork(int, UserPathWork *, float, float, int);
extern void createAttackWork(int);

void createUserPathWorkEx(int owner, UserPathWork *work, float arg3, float arg4, int arg2)
{
    work->path[0] = -1;
    work->path[1] = -1;
    work->path[2] = -1;
    work->path[3] = -1;
    work->path[4] = -1;
    work->path[5] = -1;
    work->link[0] = -1;
    work->link[1] = -1;
    work->link[2] = -1;
    work->field3C94 = -1;
    work->field3C7C = 0;
    work->field3C80 = 0;
    work->field3C84 = 0;
    work->field3C78 = 0;
    func_000FC0C0(work);
    work->field3CA0 = 1;
    work->field3CA4 = 0;
    work->field3CA8 = 0;
    work->field3CAC = 0;
    work->field3CB0 = 0;
    createUserPathWork(owner, work, arg3, arg4, arg2);
    createAttackWork(owner);
}
