typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern struct { char pad[0x170]; float speed; } gcGlobalVar;
extern unsigned char padManagerData[];
extern float D_0017B718;
extern int GAMEUTIL_get_node_posi_by_id(Vec4 *, int, int);
extern void GAMEUTIL_get_direction_by_yaw_pitch(Vec4 *, float, float);
extern char *GetLayoutClass(int);
extern int GetSkeletonFocusNodeDirect(int);

static inline float fsqrt(float x)
{
    float r;
    __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

static inline void vecScale(void *d, void *s, float k)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(s), "r"(k) : "memory");
}

static inline void vecAdd(void *d, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline float dz(float v, float a, float d)
{
    return (v < 0.0f ? -v : v) < d ? 0.0f : (v < 0.0f ? -1.0f : 1.0f) * (((v < 0.0f ? -v : v) - d) * (a / (a - d)));
}

static void func_000E41A0(Vec4 *out, Vec4 *focus, int obj, float *yaw, float *pitch)
{
    Vec4 dir;
    Vec4 node;
    char *lay;
    float dist;
    float sx, sy;
    float t, mag, inv, ax, ay, dx, dy, nx, ny;

    dist = D_0017B718;
    lay = GetLayoutClass(obj);
    sx = 0.0f;
    if (*(char **)(lay + 0x1A8) != 0
        && GAMEUTIL_get_node_posi_by_id(&node, obj, GetSkeletonFocusNodeDirect(*(int *)(*(char **)(lay + 0x1A8) + 8))) == 1)
        focus->q = node.q;
    else
        focus->q = (*(Vec4 **)(lay + 0x134))->q;
    if (!(*(int *)padManagerData & 1))
        sx = padManagerData[0x57] / 127.5f - 1.0f;
    sy = -(padManagerData[0x56] / 127.5f - 1.0f);
    t = sy * sy + sx * sx;
    if (t < 0.15999997f) {
        sx = 0.0f;
        sy = sx;
    } else {
        mag = fsqrt(t);
        inv = 1.0f / mag;
        ny = sy * inv;
        nx = sx * inv;
        if (1.0f < mag) {
            sy = ny;
            sx = nx;
        } else {
            ay = ny;
            if (ay < 0.0f)
                ay = -ay;
            ax = nx;
            if (ax < 0.0f)
                ax = -ax;
            dy = ay * 0.39999998f;
            dx = ax * 0.39999998f;
            sy = dz(sy, ay, dy);
            sx = dz(sx, ax, dx);
        }
    }
    sy = sy < 0.0f ? sy * -sy : sy * sy;
    sx = sx < 0.0f ? sx * -sx : sx * sx;
    sy = sy * 1.5f;
    sx = sx * 1.5f;
    *yaw += sy * gcGlobalVar.speed;
    *pitch += sx * gcGlobalVar.speed;
    if (*pitch < 0.0f ? *pitch <= -1.5550882f : 1.5550882f <= *pitch)
        *pitch = *pitch < 0.0f ? -1.5550882f : 1.5550882f;
    GAMEUTIL_get_direction_by_yaw_pitch(&dir, *yaw, *pitch);
    if (0.0f < *(float *)(*(char **)(GetLayoutClass(obj) + 0x1A8) + 0xC))
        dist = *(float *)(*(char **)(GetLayoutClass(obj) + 0x1A8) + 0xC);
    vecScale(&dir, &dir, -dist);
    vecAdd(out, focus, &dir);
}
