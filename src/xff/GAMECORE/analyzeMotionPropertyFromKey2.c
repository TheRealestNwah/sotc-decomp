typedef struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
    int x14;
    int x18;
    char pad[0x14];
} MotionPredict;

extern int PredictMotionOrientByScriptCtrl(int);
extern void PredictMotionChangeState(MotionPredict *, int, int);
extern void analyzeMotionProperty(int, int, int, int, int, float, float);

#ifdef NONMATCHING
int analyzeMotionPropertyFromKey2(char *obj, int a1, int a2, int a3, int t0)
{
    MotionPredict p;
    int v;

    v = PredictMotionOrientByScriptCtrl(*(int *)(obj + 8));
    if (v != 0) {
        p.x0 = 0;
        p.x4 = 0;
        p.x14 = 0;
        p.x18 = 0;
        PredictMotionChangeState(&p, *(int *)(obj + 8), v);
        if (p.x14 != 0) {
            analyzeMotionProperty(*(int *)(obj + 8), p.x14, a2, a3, t0, *(float *)(obj + 0xB0), 0.0f);
            return p.x14;
        }
    }
    return 0;
}
#endif
