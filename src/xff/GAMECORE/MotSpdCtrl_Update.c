typedef struct {
    float rot;
    float start;
    float end;
    float spd;
    unsigned char active;
    unsigned char dir;
    char pad[2];
    float *rate;
} MotSpd;

typedef struct { char pad[0x180]; float speed; } GcGlobal;

extern char *GetCharacterClass(void *);
extern float iosGetCosf(float);
extern GcGlobal gcGlobalVar;

void MotSpdCtrl_Update(MotSpd *m, void *obj)
{
    float *rate;
    float rot;
    float v;
    float t;
    float d;
    float r;

    rate = m->rate;
    if (rate == 0)
        return;
    rot = m->rot;
    if (rot > 0.0f) {
        d = 3.1415926f / (rot >= 3.1415926f ? rate[1] : rate[2]);
        r = rot - d * gcGlobalVar.speed;
        m->rot = r;
        if (m->dir == 0 || r >= 3.1415926f) {
            v = iosGetCosf((r + 1.0f) * 0.5f * m->start);
            if (v < m->rate[0])
                v = m->rate[0];
            m->dir = 0;
        } else {
            t = 6.2831852f - r;
            v = (m->end * (3.1415926f - t) + rate[0] * t) * 0.318309886f;
        }
        v = m->spd * (v * v);
        *(float *)(GetCharacterClass(obj) + 0x524) = v * v;
    } else if (rot < 0.0f) {
        m->rot = 0.0f;
        *(float *)(GetCharacterClass(obj) + 0x524) = m->start;
        m->active = 0;
        m->dir = 0;
    }
}
