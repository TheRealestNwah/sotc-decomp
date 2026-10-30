typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

typedef struct {
    char geo[0x40];
    Vec4 pos;
} ClipResult;

typedef struct {
    char pad0[4];
    void *owner;
    void *col;
    char padC[0x1C0 - 0xC];
    Vec4 start;
    Vec4 end;
    int hit;
} Snipe;

extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern void get_snipe_position_decide_parameter_game_camera(float *, float *, void *);
extern void get_hope_camera_direction_nico_sight_on(float *, Snipe *);
extern int CAM_get_camera_space_axisXY(float *, float *, float *, float);
extern void GAMEUTIL_get_offset_position_by_option_space(float *, float *, float *, int, float *, float *, float *);
extern void func_0006EF28(float *, Snipe *, float *, float *, float *);
extern void *GAMEUTIL_get_riding_horse_object(void *);
extern int CollisionObjectJudgeCallbackExceptOneObj();
extern int CollisionPlaneJudgeCallbackArrow();
extern int ClipCollisionDirectCallBack(ClipResult *, float *, float *, void *, int (*)(), int, int, int (*)(),
                                       void *);

static inline void vecScale(float *out, float *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}

static inline void vecAdd(float *out, float *a, float *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_0006ED88(Snipe *s, int noClip, float len)
{
    Vec4 pos;
    Vec4 param;
    Vec4 ax;
    Vec4 ay;
    Vec4 dir;
    Vec4 fwd;
    Vec4 tmp;
    ClipResult clip;
    void *cam = get_game_camera(get_main_cameraman());

    get_snipe_position_decide_parameter_game_camera(pos.f, param.f, cam);
    get_hope_camera_direction_nico_sight_on(dir.f, s);
    CAM_get_camera_space_axisXY(ax.f, ay.f, dir.f, 0.0f);
    GAMEUTIL_get_offset_position_by_option_space(s->start.f, pos.f, param.f, 1, ax.f, ay.f, dir.f);
    func_0006EF28(fwd.f, s, ax.f, ay.f, dir.f);
    vecScale(tmp.f, fwd.f, -param.f[2]);
    vecAdd(s->start.f, s->start.f, tmp.f);
    vecScale(tmp.f, fwd.f, len);
    vecAdd(s->end.f, s->start.f, tmp.f);
    s->hit = 0;
    if (noClip == 0) {
        int r = ClipCollisionDirectCallBack(&clip, s->start.f, s->end.f, s->col,
                                            CollisionObjectJudgeCallbackExceptOneObj, 0, 0,
                                            CollisionPlaneJudgeCallbackArrow,
                                            GAMEUTIL_get_riding_horse_object(s->owner));

        if (r == 1) {
            s->end.q = clip.pos.q;
            s->hit = r;
        }
    }
}
