typedef float Vec4[4] __attribute__((aligned(16)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    Vec4 f;
} VecQ;

typedef struct {
    float x0;
    float x4;
    float x8;
    int xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    float x20;
    float x24;
} RegionParam;

extern void GAMEUTIL_add_local_offset_root_position(float *, void *, float, float, float);
extern void GAMEUTIL_get_local_quaternion(float *, void *);
extern char *GetLayoutClass(void *);
extern float GAMEUTIL_is_inside_of_region_ratio(int, float *, float *, float *, float, float, float, float, float, float);

static float func_000E1ED8(void *obj, void *unused, RegionParam *prm, char *target)
{
    VecQ tgt;
    Vec4 pos;
    Vec4 q;
    float r;

    GAMEUTIL_add_local_offset_root_position(pos, obj, prm->x0, prm->x4, prm->x8);
    GAMEUTIL_get_local_quaternion(q, obj);
    tgt.q = *(u_long128 *)(target + 0xA0);
    tgt.f[1] = (*(float **)(GetLayoutClass(*(void **)(target + 0x23C)) + 0x134))[1];
    r = GAMEUTIL_is_inside_of_region_ratio(prm->xC, tgt.f, pos, q, prm->x10, prm->x14, prm->x18, prm->x1C, prm->x20, prm->x24);
    if (r < 0.0f) {
        r = 0.0f;
    }
    return r;
}
