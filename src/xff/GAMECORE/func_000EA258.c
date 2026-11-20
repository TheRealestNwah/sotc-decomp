/* Parked attempt: 2 differing words (the Original sets $a2 before $f12 for CAM_get_camera_position_by_look_at). The dst stores go through a union so they may alias the following *mode loads. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern char *get_camera_lws_animation_param(int);
extern float CAM_get_interp_ratio_by_time(int, float, float, float, float);
extern void CAM_get_interp_cam_and_look_at_posi(void *, void *, void *, void *, void *, void *, int, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);
extern float get_mode_common_data_filter_base_dist_to_look_at(void *);
extern void func_000EA508(void *, void *, void *, void *);
extern void CAM_get_camera_position_by_look_at(void *, void *, void *, float);
extern void CAM_get_safety_cam_and_look_at_posi(void *, void *, void *, void *, void *, int, int);
extern float func_000E6B00(void *);

#define F(p, o) (*(float *)((char *)(p) + (o)))
typedef union { float f; char *p; } FloatOrPtr;
#define FU(p, o) (((FloatOrPtr *)((char *)(p) + (o)))->f)
#define I(p, o) (*(int *)((char *)(p) + (o)))

static void func_000EA258(char *cam, char **mode, int arg2)
{
    s128 pos[1];
    s128 dir[1];
    s128 look[1];
    char *to = cam + 0x110;
    char *from = cam + 0x200;
    char *dst = cam + 0x230;
    char *base = cam + 0x140;
    float r1;
    float r2;
    float t1;
    float t2;
    float dist;
    char *lws;

    switch (I(cam, 0x8C)) {
    case 0:
    case 1:
        lws = get_camera_lws_animation_param(I(cam, 0x90));
        r1 = CAM_get_interp_ratio_by_time(1, F(cam, 0xD4), F(cam, 0x100), F(lws, 0x8C), 0.0f);
        r2 = CAM_get_interp_ratio_by_time(1, F(cam, 0xD4), F(cam, 0x100), F(lws, 0x90), 0.0f);
        CAM_get_interp_cam_and_look_at_posi(dst, dst + 0x10, to, to + 0x10, from, from + 0x10, I(cam, 0xD0), r1, r2);
        F(dst, 0x20) = GAMEUTIL_get_interp_value(F(from, 0x20), F(to, 0x20), r1);
        F(dst, 0x24) = GAMEUTIL_get_interp_value(F(from, 0x24), F(to, 0x24), r2);
        F(dst, 0x28) = GAMEUTIL_get_interp_value(F(from, 0x28), F(to, 0x28), r2);
        break;
    case 2:
        t1 = CAM_get_interp_ratio_by_time(1, F(cam, 0xD4), F(cam, 0x104), F(cam, 0xEC), 0.0f);
        t2 = CAM_get_interp_ratio_by_time(1, F(cam, 0xD4), F(cam, 0x104), F(cam, 0xF0), 0.0f);
        dist = F(cam, 0xF4);
        if (dist <= 0.0f) {
            dist = get_mode_common_data_filter_base_dist_to_look_at(mode);
        }
        look[0] = *(s128 *)((char *)mode + 0xFD0);
        func_000EA508(dir, look, cam, mode);
        CAM_get_camera_position_by_look_at(pos, dir, look, dist);
        if (I(cam, 0xD8) == 2) {
            CAM_get_safety_cam_and_look_at_posi(pos, look, pos, look, mode, arg2, 1);
        } else {
            CAM_get_safety_cam_and_look_at_posi(pos, look, pos, look, mode, arg2, 0);
        }
        CAM_get_interp_cam_and_look_at_posi(dst, dst + 0x10, base, base + 0x10, pos, look, I(cam, 0xD0), t1, t2);
        FU(dst, 0x20) = GAMEUTIL_get_interp_value(func_000E6B00(mode), F(base, 0x20), t1);
        FU(dst, 0x24) = GAMEUTIL_get_interp_value(F(*mode, 0x160), F(base, 0x24), t2);
        F(dst, 0x28) = GAMEUTIL_get_interp_value(F(*mode, 0x18C), F(base, 0x28), t2);
        break;
    case 3:
    case 4:
        break;
    }
}
#endif
