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

int MotSpdCtrl_StartExt(MotSpd *m, void *obj, float spd);
void MotSpdCtrl_Reset(char *p);

void MotSpdCtrl_Init(char *p, int a)
{
    MotSpdCtrl_Reset(p);
    *(int *)(p + 0x14) = a;
}

int MotSpdCtrl_Start(int a, int b, int c, int d)
{
    return ((int (*)(int, int, int, int, float))MotSpdCtrl_StartExt)(a, b, c, d, 1.0f);
}

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

void MotSpdCtrl_Reset(char *p)
{
    *(char *)(p + 0x10) = 0;
    *(int *)(p + 0x0) = 0;
    *(char *)(p + 0x11) = 0;
}
