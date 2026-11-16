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
extern void func_000D80A0(char *, char *, char *, char *, float);
extern void func_000D8380(char *, char *, char *, char *);
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
    func_000D80A0(mgr, cam, mode, arg3, dt);
    func_000D8380(mgr, cam, mode, arg3);
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
