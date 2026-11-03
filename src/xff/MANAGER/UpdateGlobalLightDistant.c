#ifdef NONMATCHING
/* original recomputes lights + i * 0x40 at the found point; otherwise matches. */
typedef int s128 __attribute__((mode(TI)));
typedef union {s128 q;float f[4];} Color;

typedef struct {
    Color color;
    float dir[3];
    float pad1C;
    float brightness;
    float power;
    float scaled;
    char pad2C[4];
    signed char id;
    char pad31[0xF];
} DistantLight;

typedef struct {
    Color color;
    float intensity;
    int id;
    float dir[3];
} DistantParam;

extern float iosCalcFColorToBrightness(float *);
extern void func_0007CDF8(void *);

static inline void calcColorParam(DistantLight *l)
{
    float b;
    float v;

    b = iosCalcFColorToBrightness(l->dir);
    v = b * l->power;
    l->brightness = b;
    if (v < 0.0f) {
        v = -v;
    }
    l->scaled = v;
}

void UpdateGlobalLightDistant(DistantLight *lights, void *parameter)
{
    DistantParam *p = (DistantParam *)((char *)parameter + 0x10);
    DistantLight *l = 0;
    int i;

    for (i = 0; i < 3; i++) {
        if (lights[i].id == p->id) {
            l = &lights[i];
            break;
        }
    }
    l->color.q = p->color.q;
    l->power = 1.0f;
    l->dir[0] = p->dir[0] * p->intensity;
    l->dir[1] = p->dir[1] * p->intensity;
    l->dir[2] = p->dir[2] * p->intensity;
    calcColorParam(l);
    func_0007CDF8(lights);
}
#endif
