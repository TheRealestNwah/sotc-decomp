typedef struct {
    char pad0[0x58];
    float baseYaw;
    char pad5C[0x74 - 0x5C];
    float yawMin;
    float yawMax;
    char pad7C[0x88 - 0x7C];
    float p88;
    float p8C;
    float p90;
    float p94;
    char pad98[0xB0 - 0x98];
    float yaw;
    char padB4[0xD0 - 0xB4];
    int d0;
    int padD4;
    int d8;
    int dc;
    int e0;
    int e4;
} WormCtrl;

extern void _resetBaseMoveWork(void *, WormCtrl *);
extern void resetVelocityWormCtrlWork(void *, WormCtrl *);
extern void func_00113078(WormCtrl *);

static void func_00112FC8(void *obj, WormCtrl *w)
{
    _resetBaseMoveWork(obj, w);
    resetVelocityWormCtrlWork(obj, w);
    w->yaw = w->baseYaw;
    w->yawMin = -3.1415925026f;
    w->yawMax = 3.1415925026f;
    w->dc = 1;
    w->p88 = -5.0f;
    w->p8C = 10.0f;
    w->p90 = -0.5f;
    w->p94 = -2.0f;
    w->d0 = 0;
    w->d8 = 0;
    w->e0 = 0;
    w->e4 = 0;
    func_00113078(w);
}
