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

extern char *GetCharacterClass(void *);

int MotSpdCtrl_StartExt(MotSpd *m, void *obj, float spd)
{
    if (m->rate == 0)
        return 0;
    m->spd = spd;
    if (m->rate[1] == 0.0f && m->rate[2] == 0.0f)
        return 0;
    if (m->active == 0) {
        m->active = 1;
        m->start = *(float *)(GetCharacterClass(obj) + 0x524);
        m->rot = 6.283185307179586f;
        m->dir = 0;
        return 1;
    }
    m->dir = 1;
    m->rot = 6.283185307179586f;
    m->end = *(float *)(GetCharacterClass(obj) + 0x524);
    return 0;
}
