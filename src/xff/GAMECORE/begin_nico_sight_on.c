typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) Vec4;
typedef struct {
    int on;
    void *target;
    int arg;
    char yp[0x14C - 0xC];
    int f14C;
    s128 q150;
    char spring[0x1A0 - 0x160];
    int f1A0;
    int f1A4;
    char pad1A8[8];
    s128 q1B0;
} Sight;
extern s128 ZeroVector;
extern s128 ZeroPoint;
extern void *memset(void *, int, unsigned int);
extern float func_000706D0(void *);
extern void begin_nico_yaw_pitch_cntrl(void *, float, float);
extern void reset_double_spring_interp_cntrl3D(void *, Vec4 *);
extern void func_0006ED88(Sight *, int, float);
extern void func_0006F230(Sight *, int, float, float);

void begin_nico_sight_on(Sight *s, void *target, int arg, float f)
{
    Vec4 v2;
    Vec4 v;
    void *yp = s->yp;

    memset(&v, 0, sizeof(v));
    v.x = func_000706D0(target);
    s->on = 1;
    s->target = target;
    s->arg = arg;
    v2 = v;
    begin_nico_yaw_pitch_cntrl(yp, func_000706D0(target), 0.0f);
    s->f14C = 0;
    s->q150 = ZeroVector;
    reset_double_spring_interp_cntrl3D(s->spring, &v2);
    s->f1A0 = 0;
    s->f1A4 = 0;
    s->q1B0 = ZeroPoint;
    func_0006ED88(s, 1, f);
    func_0006F230(s, 1, 0.0f, 0.0f);
}
