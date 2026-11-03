#ifdef NONMATCHING /* near-miss: register allocation / scheduling differences remain */
typedef struct {
    int motion;
    int pad4[7];
    int force;
    int pad24[7];
} MotionState;

typedef struct {
    MotionState state;
    int arg;
    int flag;
} MotionPredict;

typedef struct {
    int arg;
    int a;
    int b;
} PredictResult;

typedef struct {
    char pad0[0x1C0];
    MotionState state;
} CharacterClass;

extern CharacterClass *GetCharacterClass(int);
extern int func_00053F80(PredictResult *, CharacterClass *, MotionPredict *, int);
extern void func_00054F18(PredictResult *, CharacterClass *, MotionPredict *, int);

void PredictMotionChangeState(PredictResult *out, int chara, int arg)
{
    CharacterClass *cls;
    MotionPredict p;
    int r;

    cls = GetCharacterClass(chara);
    p.state = cls->state;
    p.arg = arg;
    arg = p.state.motion;
    p.state.force = 1;
    out->b = 0;
    out->arg = p.arg;
    out->a = 0;
    p.flag = 0;
    r = func_00053F80(out, cls, &p, arg);
    if (r >= 0) {
        if (r == 0) {
            func_00054F18(out, cls, &p, arg);
        }
    }
}
#endif
