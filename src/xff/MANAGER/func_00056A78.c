typedef struct {
    char pad0[0x5C];
    int frames;
    char pad60[0x68 - 0x60];
    unsigned int flags;
} Motion;

typedef struct {
    Motion *motion;
    int pad4;
    float time;
} MotState;

typedef struct {
    char pad0[0x1C0];
    MotState mot;
    char pad1CC[0x360 - 0x1CC];
    char blended;
    char pad361[0x52B - 0x361];
    signed char interp;
    char pad52C[0x538 - 0x52C];
    signed char useFrames;
    char pad539[0x720 - 0x539];
    float interpLen;
    float interpRate;
    char pad728[0x73C - 0x728];
    float blend;
    float blendLen;
    float blendRate;
} CharClass;

typedef struct {
    char pad0[8];
    int active;
    char padC[0x30 - 0xC];
} MotReq;

extern CharClass *GetCharacterClass(void);
extern void func_00056780(MotReq *, int, float);
extern int func_00055E70(MotReq *, int, float);

static int func_00056A78(int id, float dt)
{
    CharClass *c = GetCharacterClass();
    MotReq req;
    Motion *m;
    MotState *ms;
    float t;
    float blend;

    func_00056780(&req, id, dt);
    c->blended = 0;
    if (req.active != 0) {
        c->blended = 1;
        if (func_00055E70(&req, id, dt) == 0)
            return 0;
    }
    ms = &c->mot;
    m = ms->motion;
    t = ms->time;
    if ((m != 0 && ((m->flags >> 18) & 1)) || c->interpLen == 0.0f || c->interp == 0)
        c->interpRate = 1.0f;
    else if (c->interpLen <= t) {
        c->interpLen = 0.0f;
        c->interpRate = 1.0f;
    } else
        c->interpRate = t / c->interpLen;
    if (c->blendLen == 0.0f)
        c->blendRate = 1.0f;
    else if (c->blendLen <= t)
        c->blendRate = 1.0f;
    else
        c->blendRate = t / c->blendLen;
    blend = c->blend;
    if (blend < 1.0f) {
        if (c->useFrames != 0 && m != 0)
            blend += dt * ((float)m->frames / c->interpLen);
        else
            blend += dt * 3.0f;
        if (1.0f <= blend)
            c->blend = 1.0f;
        else
            c->blend = blend;
    }
    return 1;
}
