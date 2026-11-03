#ifdef NONMATCHING /* 44 instruction diffs: the original stores state into the struct after the 64-byte block copy and then reloads it; gcc keeps the store ahead of the copy here */
typedef struct {
    int v[16];
} MotBlk;
typedef struct {
    char pad[0x1C0];
    MotBlk blk;
} CharClass;
typedef struct {
    MotBlk blk;
    int state;
    int flag;
} MotPredict;
typedef struct {
    int state;
    int a;
    int b;
} MotResult;
extern CharClass *GetCharacterClass(int);
extern int func_00053F80(MotResult *, CharClass *, MotPredict *, int);
extern void func_00054F18(MotResult *, CharClass *, MotPredict *, int);
void PredictMotionChangeState(MotResult *res, int chr, int state)
{
    CharClass *cls;
    MotPredict pr;
    int r;
    int key;

    cls = GetCharacterClass(chr);
    pr.state = state;
    pr.blk = cls->blk;
    pr.blk.v[8] = 1;
    key = pr.blk.v[0];
    res->b = 0;
    res->state = pr.state;
    res->a = 0;
    pr.flag = 0;
    r = func_00053F80(res, cls, &pr, key);
    if (r < 0) {
        return;
    }
    if (r != 0) {
        return;
    }
    func_00054F18(res, cls, &pr, key);
}
#endif
