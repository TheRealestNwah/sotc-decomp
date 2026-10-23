typedef union {
    struct {
        float start;
        float end;
        float from;
        float to;
        float cur;
        int kind;
    } s;
    char alias;
} FadeParam;

typedef struct {
    char pad[0x168];
    float time;
} GlobalVar;

extern GlobalVar gcGlobalVar;

void setFadeParam(FadeParam *fade, int kind, float to, float time)
{
    fade->s.start = gcGlobalVar.time;
    fade->s.end = gcGlobalVar.time + time;
    fade->s.from = fade->s.cur;
    fade->s.to = to;
    fade->s.kind = kind;
}
