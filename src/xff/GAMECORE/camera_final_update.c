#include "gamecore/camera_final_update.h"

typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;
typedef struct {
    char pad0[0x20];
    Vec4 rot;
    char pad30[0x10];
    Vec4 ofs;
    char pad50[0x20];
    Vec4 look;
    char pad80[0x10];
} Blend;
extern char *get_cur_using_lws_anime_mode_base_class(char *);
extern void copy_mode_common_camera_data(void *, void *);
extern void *CAM_get_target_obj(void *);
extern char *GetLayoutClass(void *);
extern int get_blend_sub_camera_lws_animation(Blend *, void *, int, void *);
extern int CAM_get_camera_space_axisXY(void *, void *, void *, float);
extern int GAMEUTIL_get_offset_position_by_option_space(void *, void *, void *, int, void *, void *, void *);
extern int camera_collision_check_with_keep(void *, char *, void *, void *, char *, int);
extern int CAM_get_new_look_at_posi_from_camera_posi_and_rotXY(void *, int, void *, void *, void *, float, float, float);
extern void update_by_cam_and_look_at_posi_mode_common_camera_data(void *);
extern int GAMEUTIL_is_yaw_pitch_get_direction(void *);
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define Q(p, o) (*(s128 *)((char *)(p) + (o)))
static inline void scaleVector(void *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}
static inline void addVector(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
typedef struct {
    float f[4];
} __attribute__((aligned(16))) Vec4_func_000D80A0;
typedef struct {
    float m[4][4];
} __attribute__((aligned(16))) Mat4;
extern void *memset(void *, int, unsigned int);
extern void doit_double_spring_interp_cntrl3D(void *, void *, int, float);
extern int GAMEUTIL_is_nearly_equal_zero3D(void *, float);
extern void iosRotMatrixAxis(void *, void *, int, float);
extern void iosApplyRotMatrix(void *, void *, void *);
extern int GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, void *);
extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(void *, float, float);
typedef struct {
    Vec4_func_000D80A0 pos;
    Vec4_func_000D80A0 at;
    Vec4_func_000D80A0 dir;
    float yaw;
    float pitch;
    float dist;
} CamPos;
#define DEG 0.0174532924f
static inline void scaleVecXYZ(void *out, void *in, float s)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "qmtc2.ni %2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(in), "r"(s) : "memory");
}
static inline void addVecXYZ(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}
extern void constructor_double_spring_interp_cntrl3D(char *, float, float);
extern void set_param_double_spring_interp_common(char *, float, float, float, float);
typedef unsigned int u_long128 __attribute__((mode(TI)));
extern int *DldSysUndefSymbol;
extern char D_0017B620[];
extern char D_0017B660[];
extern u_long128 D_0017B670;
extern char IdentityQuaternion[];
extern char ZeroPoint[];
extern void SetGeometryPointerGlobalStatePointer(void *, void *, void *, void *, void *);
extern int is_base_mode_manager_update_game_camera_param_manager(void *);
extern int is_same_camera_lws_animation(int, void *);
extern void end_camera_lws_animation(int);
extern int boot_camera_lws_animation(void *, void *, int, int, int, float);
static inline char *dldResolve(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    int *t = off != 0 ? *(int **)((char *)h - off) : 0;
    return t != 0 && t != DldSysUndefSymbol ? (char *)t[4] + ((v >> 18) & 0xFFF) * ((int *)t[2])[3] : 0;
}

static void func_000D80A0(char *self, char *c, void *mode, int unused, float t);
static void func_000D8380(int *anim, char *cam, char *mgr);

void doit_camera_final_update(char *mgr, char *cam, char *mode, char *arg3, float dt)
{
    Blend bl;
    s128 ax[1];
    s128 ay[1];
    s128 off[1];
    s128 tmp[1];
    s128 col[1];
    s128 unused[2];
    char *base;
    char *cd;
    char *pos;
    char *rot;
    int ok;

    cd = cam + 0x120;
    base = get_cur_using_lws_anime_mode_base_class(mode);
    copy_mode_common_camera_data(cd, cam + 0xE0);
    F(cam, 0x1C4) = F(cam, 0x1C0);
    ((void (*)(char *, char *, char *, char *, float))func_000D80A0)(mgr, cam, mode, arg3, dt);
    ((void (*)(char *, char *, char *, char *))func_000D8380)(mgr, cam, mode, arg3);
    if (base != 0 && I(base, 0x9C) != 0)
        goto out;
    pos = cam + 0x130;
    if (get_blend_sub_camera_lws_animation(&bl, cd, I(GetLayoutClass(CAM_get_target_obj(cam + 0x23C)), 0x134), pos) != 1)
        goto out;
    ok = 1;
    rot = cam + 0x140;
    CAM_get_camera_space_axisXY(ax, ay, rot, F(cam, 0x1C0));
    if (GAMEUTIL_get_offset_position_by_option_space(off, cd, &bl.ofs, 1, ax, ay, rot) == ok) {
        if (camera_collision_check_with_keep(col, cam, cd, off, arg3, 0) == ok)
            Q(cd, 0) = col[0];
        else
            Q(cd, 0) = off[0];
        scaleVector(tmp, rot, F(cam, 0x158));
        addVector(pos, cd, tmp);
    }
    if (CAM_get_new_look_at_posi_from_camera_posi_and_rotXY(pos, 1, pos, cd, rot, bl.rot.f[0], bl.rot.f[1], F(cam, 0x158)) == 1) {
        update_by_cam_and_look_at_posi_mode_common_camera_data(cd);
        ok = CAM_get_camera_space_axisXY(ax, ay, rot, F(cam, 0x1C0));
    }
    if (ok == 1) {
        if (GAMEUTIL_get_offset_position_by_option_space(pos, pos, &bl.look, 1, ax, ay, rot) == ok) {
            update_by_cam_and_look_at_posi_mode_common_camera_data(cd);
            ok = GAMEUTIL_is_yaw_pitch_get_direction(rot);
        }
        if (ok == 1) {
            if (GAMEUTIL_is_nearly_equal_zero(bl.rot.f[2], 0.0001f) == 0)
                F(cam, 0x1C4) += bl.rot.f[2];
            goto out;
        }
    }
    copy_mode_common_camera_data(cd, cam + 0xE0);
out:
    Q(cam, 0x1880) = bl.rot.q;
    Q(cam, 0x1890) = bl.ofs.q;
    Q(cam, 0x18B0) = bl.look.q;
}

static void func_000D80A0(char *self, char *c, void *mode, int unused, float t)
{
    Vec4_func_000D80A0 tgt;
    Vec4_func_000D80A0 axis;
    Vec4_func_000D80A0 dir;
    Mat4 m;
    float yaw;
    float pitch;
    char *base;
    int p;
    int r;
    float x;
    CamPos *cp;

    memset(&tgt, 0, 0x10);
    p = 0;
    base = ((char * (*)(void *))get_cur_using_lws_anime_mode_base_class)(mode);
    if (base != 0) {
        p = *(int *)(base + 0x98);
        if (p == 0) {
            x = *(float *)(c + 0xC);
            if (0.0f < x) {
                tgt.f[0] = x * (*(float *)(base + 0xA4) * DEG);
            } else if (x < 0.0f) {
                tgt.f[0] = -x * (*(float *)(base + 0xA8) * DEG);
            }
            x = *(float *)(c + 0x10);
            if (0.0f < x) {
                tgt.f[1] = -x * (*(float *)(base + 0xAC) * DEG);
            } else if (x < 0.0f) {
                tgt.f[1] = x * (*(float *)(base + 0xB0) * DEG);
            }
        }
    }
    doit_double_spring_interp_cntrl3D(self + 0x10, &tgt, p, t);
    if (GAMEUTIL_is_nearly_equal_zero3D(self + 0x40, 0.0001f)) {
        return;
    }
    r = ((int (*)(int, void *, void *, float))CAM_get_camera_space_axisXY)(0, &axis, c + 0x140, 0.0f);
    cp = (CamPos *)(c + 0x120);
    if (r != 1) {
        return;
    }
    iosRotMatrixAxis(&m, &axis, 1, *(float *)(self + 0x40));
    iosApplyRotMatrix(&dir, &m, &cp->dir);
    if (GAMEUTIL_get_yaw_pitch_by_direction(&yaw, &pitch, &dir) != r) {
        return;
    }
    cp->yaw = yaw;
    cp->pitch = GAMEUTIL_increase_pitch(0, 0, pitch, *(float *)(self + 0x44), 1.48352980613708496093750f, -1.48352980613708496093750f);
    GAMEUTIL_get_direction_by_yaw_pitch(&cp->dir, cp->yaw, cp->pitch);
    scaleVecXYZ(&dir, &cp->dir, cp->dist);
    addVecXYZ(&cp->at, &cp->pos, &dir);
}

void constructor_camera_final_update(char *c)
{
    *(int *)c = -1;
    c += 0x10;
    constructor_double_spring_interp_cntrl3D(c, 0.0001f, 0.0f);
    set_param_double_spring_interp_common(c, 6.0f, -1.0f, 3.0f, -1.0f);
}

static void func_000D8380(int *anim, char *cam, char *mgr)
{
    char *layout;
    char *lws;

    layout = GetLayoutClass(CAM_get_target_obj(cam + 0x23C));
    D_0017B670 = **(u_long128 **)(layout + 0x134);
    SetGeometryPointerGlobalStatePointer(D_0017B620, D_0017B660, &D_0017B670, IdentityQuaternion, ZeroPoint);
    if (is_base_mode_manager_update_game_camera_param_manager(mgr + 0x50) != 1)
        return;
    lws = dldResolve(*(unsigned int **)(*(char **)cam + 0x14));
    if (is_same_camera_lws_animation(*anim, lws))
        return;
    end_camera_lws_animation(*anim);
    *anim = boot_camera_lws_animation(lws, D_0017B620, 0, 0, 0, 0);
}
