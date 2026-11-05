struct GcGlobal {
    char pad[0x178];
    float time;
};
extern struct GcGlobal gcGlobalVar;

struct RollState {
    float cur;
    float prev;
    float last;
};

struct RollFade {
    int state;
    float a;
    float b;
    int unkC;
    float time;
};

extern float B_0019CD3C;
extern float D_0017AFF0;
extern struct RollState D_0017B018;
extern struct RollFade B_0019CD10;
extern void func_000BC988(int);

static inline void startRollFade(float a, float b)
{
    func_000BC988(4);
    B_0019CD10.state = 1;
    B_0019CD10.time = gcGlobalVar.time;
    B_0019CD10.a = a;
    B_0019CD10.b = b;
}

void setrollup(float value)
{
    float prev;
    float limit;

    if (B_0019CD3C > 0.0f)
        return;
    if (value == D_0017B018.cur)
        return;
    D_0017B018.cur = value;
    prev = D_0017B018.last;
    limit = D_0017AFF0 - 0.001f;
    D_0017B018.last = value;
    D_0017B018.prev = prev;
    if (prev < limit && limit <= value) {
        startRollFade(0.599999964237213134765625f, 0.5f);
    }
}
