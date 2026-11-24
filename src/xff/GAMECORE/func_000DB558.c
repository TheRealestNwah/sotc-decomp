/* Parked: 2 diffs (func_000DB558 2, func_000DB6C0 0).
 * Remaining: func_000DB558 sets up check_and_get_normalize_vector's a1/a2
 * in the other order (the Original fills the jal delay slot with a1 = 0).
 * The $8 mfc1 into vecLerpI and the $3 pos copy fix the coef and pos
 * registers. The union entry stops float stores from passing the copies,
 * and the memory barrier keeps the pos load after the p0 store like the
 * Original. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { s128 q; } Q;

typedef struct {
    int state;
    char pad4[0xC];
    Vec dir;
} LostTarget;

typedef struct {
    int hit;
    float yaw;
    float pitch;
    float d;
    Q p0;
    Q p1;
} VisibleAngleEntryS;
typedef union { VisibleAngleEntryS s; s128 q[3]; } VisibleAngleEntry;

typedef struct {
    int count;
    char pad4[0xC];
    VisibleAngleEntry entries[20];
    char pad_active[0x3DC - 0x3D0];
    int max;
    char pad3e0[8];
    float step;
} VisibleAngleManager;

extern Q ZeroPoint;
extern int GAMEUTIL_get_cross_position_coefficient_t_by_dist_factor(float *, float *, void *, void *, float, void *);
extern int GAMEUTIL_check_and_get_normalize_vector(float *, void *, float *);
extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(float *, float, float);
extern void CAM_get_camera_position_by_look_at(void *, void *, void *, float);
extern void *CAM_get_target_riding_obj(void *);
extern int CAM_act_ray_check_for_camera(void *, void *, void *, void *, int, void *);

static inline void vecScale(float *dst, float *src, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(dst), "r"(src), "r"(s) : "memory");
}
static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline void vecSub(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
static inline void vecLerp(float *out, float *a, float *b, float t)
{
    __asm__ __volatile__("qmtc2.ni %3, vf7\n"
                         "lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsubx.w vf8, vf0, vf7x\n"
                         "vmulax.xyz ACC, vf5, vf7x\n"
                         "vmaddw.xyz vf5, vf6, vf8w\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b), "r"(t) : "memory");
}

static inline void vecLerpI(float *out, float *a, float *b, int t)
{
    __asm__ __volatile__("qmtc2.ni %3, vf7
"
                         "lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsubx.w vf8, vf0, vf7x
"
                         "vmulax.xyz ACC, vf5, vf7x
"
                         "vmaddw.xyz vf5, vf6, vf8w
"
                         "sqc2 vf5, 0x0(%0)
"
                         : : "r"(out), "r"(a), "r"(b), "r"(t) : "memory");
}

static int func_000DB558(float *yaw, float *pitch, LostTarget *t, char *cam)
{
    Vec pos;
    Vec mid;
    Vec v;
    float coef;
    float dist;
    float y;
    float p;
    char *c60;
    char *target = cam + 0x520;
    char *look;

    if (t->state != 0) {
        c60 = cam + 0x60;
        vecScale(v, t->dir, -1.0f);
        vecAdd(pos, target, v);
        look = cam + 0x70;
        GAMEUTIL_get_cross_position_coefficient_t_by_dist_factor(&coef, &dist, look, target, *(float *)(c60 + 0x38), pos);
        do {
            { register int c8 __asm__("$8"); float *mp = mid; __asm__("mfc1 %0, %1" : "=r"(c8) : "f"(coef)); vecLerpI(mp, pos, target, c8); }
            vecSub(v, look, mid);
        } while (0);
        if (GAMEUTIL_check_and_get_normalize_vector(v, (void *)0, v) == 1) {
            GAMEUTIL_get_yaw_pitch_by_direction(&y, &p, v);
            if (1.48352981f < p)
                p = 1.48352981f;
            if (p < -1.48352981f)
                p = -1.48352981f;
            *yaw = y;
            *pitch = p;
            return 1;
        }
    }
    return 0;
}

static void func_000DB6C0(VisibleAngleManager *m, char *cam, void *c)
{
    Vec pos;
    Vec dir;
    char *c60 = cam + 0x60;
    char *target = cam + 0x520;
    float yaw = *(float *)(cam + 0xA94);
    float pitch = *(float *)(cam + 0xAA4);
    float d;
    VisibleAngleEntry *e;
    int n;
    int r;

    if (m->count >= m->max)
        m->count = 0;
    n = m->count;
    d = m->step * (float)((n + 2) / 2);
    if (n % 2 == 1)
        d = -d;
    yaw = GAMEUTIL_increase_yaw(0, yaw, d);
    GAMEUTIL_get_direction_by_yaw_pitch(dir, yaw, pitch);
    CAM_get_camera_position_by_look_at(pos, dir, cam + 0x70, *(float *)(c60 + 0x38));
    e = (VisibleAngleEntry *)((m->count * 0x30 + (int)m) + 0x10);
    e->s.hit = 0;
    e->s.pitch = 0;
    e->s.yaw = 0;
    e->s.d = 0;
    e->s.p0 = ZeroPoint;
    e->s.p1 = ZeroPoint;
    r = CAM_act_ray_check_for_camera(0, target, pos, c, 0, CAM_get_target_riding_obj(cam + 0x23C));
    e->s.hit = r;
    if (r == 1) {
        e->s.yaw = yaw;
        e->s.pitch = pitch;
        e->s.d = 0;
        e->s.p0 = *(Q *)target;
        __asm__ __volatile__("" ::: "memory");
        { register s128 x __asm__("$3") = *(s128 *)pos; e->s.p1.q = x; }
    }
    m->count++;
}

int use_db(float *a, float *b, LostTarget *t, char *c) { func_000DB6C0((void *)a, c, b); return func_000DB558(a, b, t, c); }
#endif
