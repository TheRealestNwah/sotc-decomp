extern void *GAMEUTIL_get_boss_obj(void);
extern char *GetLayoutClass(void *);
extern int strcmp(const char *, const char *);
extern const char RO_001812B8[];

typedef struct {
    int k;
    float a[3];
    float p[3];
    float b[12];
    float ang;
    float c[14];
    float d;
    float e;
    union { int i; float f; } sel;
    float g[14];
    float h;
} Pose;

typedef struct {
    char pad0[0x4C];
    float a[6];
    char pad64[0x128 - 0x64];
    float b[6];
    char pad140[0x150 - 0x140];
    float c;
    char pad154[0x160 - 0x154];
    float d;
    float e;
} Base;

static inline float angBlend(float wa, float wb, float pb, float pa)
{
    float x;
    float y;
    float d;
    float r;

    x = pb;
    y = pa;
    d = x - y;
    if ((d < 0.0f) ? (-180.0f <= d) : (d <= 180.0f)) {
        x = wa * pa + wb * pb;
    } else {
        if (pa < 0.0f)
            y = pa + 360.0f;
        else if (pb < 0.0f)
            x = pb + 360.0f;
        x = wa * y + wb * x;
        if (180.0f < x)
            x -= 360.0f;
    }
    return x;
}

static inline int useOwn(int sel, char *cam)
{
    void *boss;

    if (sel == 0)
        return 0;
    if (sel == 1)
        return 1;
    if (*(int *)(cam + 0x1360) == 4) {
        boss = GAMEUTIL_get_boss_obj();
        if (boss == 0)
            return 0;
        return strcmp(*(char **)(GetLayoutClass(boss) + 0x130), RO_001812B8) != 0;
    }
    return 1;
}

static void func_000F01B8(Pose *out, float wa, Pose *a, float wb, Pose *b, Base *x, char *cam)
{
    int use;

    out->a[0] = wa * a->a[0] + wb * b->a[0];
    out->a[1] = wa * a->a[1] + wb * b->a[1];
    out->a[2] = wa * a->a[2] + wb * b->a[2];
    if (0.0f < a->p[0] && 0.0f < b->p[0])
        out->p[0] = wa * a->p[0] + wb * b->p[0];
    if (0.0f < a->p[1] && 0.0f < b->p[1])
        out->p[1] = wa * a->p[1] + wb * b->p[1];
    if (0.0f < a->p[2] && 0.0f < b->p[2])
        out->p[2] = wa * a->p[2] + wb * b->p[2];
    out->b[0] = wa * a->b[0] + wb * b->b[0];
    out->b[1] = wa * a->b[1] + wb * b->b[1];
    out->b[2] = wa * a->b[2] + wb * b->b[2];
    out->b[3] = wa * a->b[3] + wb * b->b[3];
    out->b[4] = wa * a->b[4] + wb * b->b[4];
    out->b[5] = wa * a->b[5] + wb * b->b[5];
    out->b[6] = wa * a->b[6] + wb * b->b[6];
    out->b[7] = wa * a->b[7] + wb * b->b[7];
    out->b[8] = wa * a->b[8] + wb * b->b[8];
    out->b[9] = wa * a->b[9] + wb * b->b[9];
    out->b[10] = wa * a->b[10] + wb * b->b[10];
    out->b[11] = wa * a->b[11] + wb * b->b[11];
    out->ang = angBlend(wa, wb, b->ang, a->ang);
    out->c[0] = wa * a->c[0] + wb * b->c[0];
    out->c[1] = wa * a->c[1] + wb * b->c[1];
    out->c[2] = wa * a->c[2] + wb * b->c[2];
    out->c[3] = wa * a->c[3] + wb * b->c[3];
    out->c[4] = wa * a->c[4] + wb * b->c[4];
    out->c[5] = wa * a->c[5] + wb * b->c[5];
    out->c[6] = wa * a->c[6] + wb * b->c[6];
    out->c[7] = wa * a->c[7] + wb * b->c[7];
    out->c[8] = wa * a->c[8] + wb * b->c[8];
    out->c[9] = wa * a->c[9] + wb * b->c[9];
    out->c[10] = wa * a->c[10] + wb * b->c[10];
    out->c[11] = wa * a->c[11] + wb * b->c[11];
    out->c[12] = wa * a->c[12] + wb * b->c[12];
    out->c[13] = wa * a->c[13] + wb * b->c[13];
    if (0.0f < a->d && 0.0f < b->d && b->d != 0.001f)
        out->d = wa * a->d + wb * b->d;
    if (0.0f < a->e && 0.0f < b->e && b->e != 0.001f)
        out->e = wa * a->e + wb * b->e;

    use = useOwn(b->sel.i, cam);

    if (use == 1) {
        out->g[0] = wa * a->g[0] + wb * b->g[0];
        out->g[1] = wa * a->g[1] + wb * b->g[1];
        out->g[2] = wa * a->g[2] + wb * b->g[2];
        out->g[3] = wa * a->g[3] + wb * b->g[3];
        out->g[4] = wa * a->g[4] + wb * b->g[4];
        out->g[5] = wa * a->g[5] + wb * b->g[5];
        out->g[6] = wa * a->g[6] + wb * b->g[6];
        out->g[7] = wa * a->g[7] + wb * b->g[7];
        out->g[8] = wa * a->g[8] + wb * b->g[8];
        out->g[9] = wa * a->g[9] + wb * b->g[9];
        out->g[10] = wa * a->g[10] + wb * b->g[10];
        out->g[11] = wa * a->g[11] + wb * b->g[11];
        out->g[12] = wa * a->g[12] + wb * b->g[12];
        out->g[13] = wa * a->g[13] + wb * b->g[13];
        out->h = wa * a->h + wb * b->h;
    } else {
        out->g[0] = wa * a->g[0] + wb * x->a[0];
        out->g[1] = wa * a->g[1] + wb * x->a[1];
        out->g[2] = wa * a->g[2] + wb * x->a[2];
        out->g[3] = wa * a->g[3] + wb * x->a[3];
        out->g[4] = wa * a->g[4] + wb * x->a[4];
        out->g[5] = wa * a->g[5] + wb * x->a[5];
        out->g[6] = wa * a->g[6] + wb * x->c;
        out->g[7] = wa * a->g[7] + wb * x->b[0];
        out->g[8] = wa * a->g[8] + wb * x->b[1];
        out->g[9] = wa * a->g[9] + wb * x->b[2];
        out->g[10] = wa * a->g[10] + wb * x->b[3];
        out->g[11] = wa * a->g[11] + wb * x->b[4];
        out->g[12] = wa * a->g[12] + wb * x->b[5];
        out->g[13] = wa * a->g[13] + wb * x->d;
        out->h = wa * a->h + wb * x->e;
    }
}
