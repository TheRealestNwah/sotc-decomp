typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } QV;

typedef struct {
    float limit;
    float time;
    int lws;
    int pending;
    unsigned char lit;
    unsigned char out;
} Torch;

typedef struct {
    char pad0[0x70];
    int type;
    char pad74[0x10];
    Torch torch;
    char pad98[0x150 - 0x98];
    void *layout;
    char pad154[0x184 - 0x154];
    char *obj;
} TorchWork;

extern char gcGlobalVar[];
extern int ScriptAnimationObjDef_TORCH_LOOP;
extern int *SkelFocusDef_PLAYER_SWORD;
extern int *SkelFocusDef_PLAYER_SWORDTOP;
extern char IdentityQuaternion[];
extern char ZeroPoint[];

extern void *isysGetThisSubThread(void);
extern int _SCRSetupLWSWithTargetNodeParent(int, void *, int);
extern void _SCRStartLWS(int, int, int, void *);
extern int GAMEUTIL_is_swimming_now(void *);
extern int torchExtinguished(void *);
extern void GetMotionNodeQuaternionPos(void *, void *, void *, int, int);
extern char *GetLayoutClass(void *);
extern int CheckUnderVariableXZSurface(void *, void *, void *, void *);
extern void SetGeometryPointerNodePosState(void *, void *, int, void *, void *);
extern void SCRSetLWSGeometry(int, void *, void *, void *);
extern void isysRequestDeleteObj(int);

static inline void torchReset(Torch *t)
{
    t->lit = 0;
    t->time = 0.0f;
    t->limit = 0.0f;
    t->out = 0;
    if (t->lws != 0) {
        isysRequestDeleteObj(t->lws);
        t->lws = 0;
    }
    t->pending = 0;
}

static void func_000767D0(TorchWork *w)
{
    s128 buf[4];
    s128 geo2[1];
    s128 pos[1];
    QV top;
    s128 quat[1];
    void *th = isysGetThisSubThread();

    if (w->torch.out != 0 && w->torch.pending != 0) {
        w->torch.lit = 0;
        w->torch.time = 0.0f;
        w->torch.out = 0;
        w->torch.lws = 0;
    }
    if (0.0f < w->torch.time) {
        w->torch.time += *(float *)(gcGlobalVar + 0x180);
    }
    if (w->torch.lit == 0) {
        if (0.0f < w->torch.time && w->type == 9) {
            w->torch.lws = _SCRSetupLWSWithTargetNodeParent(ScriptAnimationObjDef_TORCH_LOOP, th,
                                                            (int)SkelFocusDef_PLAYER_SWORD);
            _SCRStartLWS(w->torch.lws, -1, 5, 0);
            w->torch.lit = 1;
        }
    }
    if (w->torch.lit == 0) {
        return;
    }
    if (w->torch.out == 0) {
        if (w->torch.limit - *(float *)(w->obj + 0x70) <= w->torch.time || GAMEUTIL_is_swimming_now(th)) {
            torchExtinguished(th);
        } else {
            if (w->layout == 0) {
                GetMotionNodeQuaternionPos(quat, pos, th, SkelFocusDef_PLAYER_SWORDTOP[2], 1);
            } else {
                pos[0] = **(s128 **)(GetLayoutClass(w->layout) + 0x134);
            }
            top.q = pos[0];
            top.f[1] += 20.0f;
            if (CheckUnderVariableXZSurface(buf, &top, pos, gcGlobalVar + 0x230)) {
                torchExtinguished(th);
            }
        }
    }
    if (w->torch.lws != 0) {
        if (w->layout != 0) {
            SetGeometryPointerNodePosState(buf, w->layout, 0, IdentityQuaternion, ZeroPoint);
            SCRSetLWSGeometry(w->torch.lws, buf, ZeroPoint, IdentityQuaternion);
        } else if (w->type != 9) {
            torchReset(&w->torch);
        } else {
            s128 *g = geo2;
            SetGeometryPointerNodePosState(g, th, SkelFocusDef_PLAYER_SWORD[2], IdentityQuaternion, ZeroPoint);
            SCRSetLWSGeometry(w->torch.lws, g, ZeroPoint, IdentityQuaternion);
        }
    }
}
