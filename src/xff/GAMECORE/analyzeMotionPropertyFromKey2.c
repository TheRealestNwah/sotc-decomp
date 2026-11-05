#ifdef NONMATCHING
typedef struct {
    int unk0;
    int unk4;
    int pad8[3];
    char *elem;
    int unk18;
    int pad1C[2];
} MotionChangeState;

typedef struct {
    char pad0[8];
    void *motion;
    char padC[0xA4];
    float scale;
} MotionKeyObj;

extern int PredictMotionOrientByScriptCtrl(void *);
extern void PredictMotionChangeState(MotionChangeState *, void *, int);
extern void analyzeMotionProperty(void *, char *, float *, float *, float *, float, float);

char *analyzeMotionPropertyFromKey2(MotionKeyObj *obj, int unused, float *len, float *speed, float *yaw)
{
    MotionChangeState state;
    int ctrl;

    ctrl = PredictMotionOrientByScriptCtrl(obj->motion);
    if (ctrl != 0) {
        state.unk0 = 0;
        state.unk4 = 0;
        state.elem = 0;
        state.unk18 = 0;
        PredictMotionChangeState(&state, obj->motion, ctrl);
        if (state.elem != 0) {
            analyzeMotionProperty(obj->motion, state.elem, len, speed, yaw, obj->scale, 0.0f);
            return state.elem;
        }
    }
    return 0;
}
#endif
