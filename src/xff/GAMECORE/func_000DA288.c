extern float func_000DA6A0(float a, float b, float c);
extern float func_000DA6C0(float a, float b, float c);

typedef struct {
    char pad0[0xE0];
    float xE0;
    float xE4;
    char padE8[4];
    float xEC;
    float xF0;
    float xF4;
    float xF8;
} CamLimit;

typedef struct {
    char pad0[0x20];
    float x20;
    float x24;
    float x28;
    float x2C;
    float x30;
    char pad34[4];
    float x38;
    char pad3C[0x1E8 - 0x3C];
    float x1E8;
    float x1EC;
    float x1F0;
} CamYaw;

static void func_000DA288(CamYaw *p, CamLimit **lp)
{
    CamLimit *l = *lp;
    float t;
    float c;
    float z = 0.0f;
    float k;

    t = func_000DA6A0(p->x2C, p->x1E8, p->x1EC);
    p->x30 = func_000DA6C0(p->x30, t, p->x1F0);
    if (p->x28 >= z)
        c = l->xF0;
    else
        c = l->xF4;
    k = 0.017453293f;
    t = func_000DA6A0(p->x20, l->xEC * k, c);
    p->x24 = func_000DA6C0(p->x24, p->x28 * t, l->xF8 * k);
    p->x38 = p->x30 + p->x24;
    if (l->xE0 * k < p->x38)
        p->x38 = l->xE0 * k;
    if (p->x38 < l->xE4 * k)
        p->x38 = l->xE4 * k;
}
