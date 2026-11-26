typedef unsigned int Vec4 __attribute__((mode(TI)));

extern Vec4 ZeroPoint, ZUnitVector, ZeroVector;
extern void constructor_game_camera_mode_local_parameter(void *);
extern void constructor_double_spring_interp_cntrl(void *, float);
extern void reset_double_spring_interp_cntrl(void *, float);
extern void constructor_camera_view_angle_cntrl(void *);
extern void CAM_constructor_target(void *, void *);
extern void CAM_constructor_target_visibility(void *);
extern void constructor_camera_target_lost_angle(void *);
extern void constructor_camera_target_approach(void *);
extern void constructor_camera_default_angle(void *);
extern void CAM_constructor_look_at_spring(void *);
extern void CAM_constructor_base_look_at(void *);
extern void CAM_reset_target_offset(void *);
extern void constructor_camera_dist_to_look_at(void *);
extern void init_camera_place_status(void *);
extern void GAMEUTIL_constructor_col_plane_info(void *);
extern void CAM_constructor_follow_rot(void *);
extern void CAM_reset_view_cut_avoid_cntrl(void *, int);
extern void CAM_reset_obstacle_avoid_cntrl(void *);
extern void constructor_camera_final_update(void *);
extern void constructor_camera_collision_data(void *);
extern void func_000ECB78(void *, void *);
extern void func_000ECBA0(void *);

#ifdef NONMATCHING /* 10 diffs: only the order of the three swc1 stores and the sq of +0x20 in the 0x60, 0x120 and 0x160 init blocks differs. The Original schedules each copy differently, so each block spells out its own store order (13 diffs with one shared inline); calls, offsets and constants match */
#define PT(v, o) Vec4 *v = (Vec4 *)(p + (o))
#define W(v, k) (((float *)&v[3])[k])

#define F(o) (*(float *)(p + (o)))
#define I(o) (*(int *)(p + (o)))
#define V(o) (*(Vec4 *)(p + (o)))

void func_000E6140(char *p, void *a1)
{
    float zero = 0.0f;
    float one = 1.0f;
    float eps = 0.0001f;
    I(0) = 0;
    I(4) = I(8) = 1;
    F(0x10) = zero;
    F(0xC) = zero;
    constructor_game_camera_mode_local_parameter(p + 0x14);
    {
        PT(v, 0x60);
        v[0] = ZeroPoint;
        v[1] = ZeroPoint;
        v[2] = ZUnitVector;
        W(v, 0) = zero;
        W(v, 1) = zero;
        W(v, 2) = 4.5f;
    }
    {
        PT(v, 0xA0);
        v[0] = ZeroPoint;
        v[1] = ZeroPoint;
        v[2] = ZUnitVector;
        W(v, 0) = W(v, 1) = zero;
        W(v, 2) = 4.5f;
    }
    {
        PT(v, 0xE0);
        v[0] = ZeroPoint;
        v[1] = ZeroPoint;
        v[2] = ZUnitVector;
        W(v, 0) = W(v, 1) = zero;
        W(v, 2) = 4.5f;
    }
    {
        PT(v, 0x120);
        v[0] = ZeroPoint;
        v[1] = ZeroPoint;
        W(v, 0) = zero;
        W(v, 1) = zero;
        v[2] = ZUnitVector;
        W(v, 2) = 4.5f;
    }
    {
        PT(v, 0x160);
        v[0] = ZeroPoint;
        v[1] = ZeroPoint;
        v[2] = ZUnitVector;
        W(v, 0) = W(v, 1) = zero;
        W(v, 2) = 4.5f;
    }
    F(0x1A0) = one;
    constructor_double_spring_interp_cntrl(p + 0x1A4, eps);
    F(0x1C4) = zero;
    constructor_camera_view_angle_cntrl(p + 0x1C8);
    constructor_double_spring_interp_cntrl(p + 0x208, eps);
    reset_double_spring_interp_cntrl(p + 0x208, one);
    F(0x228) = zero;
    F(0x22C) = F(0x230) = zero;
    F(0x234) = F(0x238) = zero;
    CAM_constructor_target(p + 0x23C, a1);
    CAM_constructor_target_visibility(p + 0x520);
    constructor_camera_target_lost_angle(p + 0x660);
    constructor_camera_target_approach(p + 0x6A0);
    constructor_camera_default_angle(p + 0x730);
    V(0xF20) = ZUnitVector;
    F(0xF30) = F(0xF34) = zero;
    I(0xF38) = I(0xF3C) = 0;
    CAM_constructor_look_at_spring(p + 0xF40);
    CAM_constructor_base_look_at(p + 0xFC0);
    V(0x1010) = ZeroPoint;
    F(0x1020) = one;
    CAM_reset_target_offset(p + 0x1030);
    constructor_camera_dist_to_look_at(p + 0x11F0);
    init_camera_place_status(p + 0x1270);
    GAMEUTIL_constructor_col_plane_info(p + 0x1440);
    CAM_constructor_follow_rot(p + 0x14A0);
    CAM_reset_view_cut_avoid_cntrl(p + 0x16B0, 1);
    CAM_reset_obstacle_avoid_cntrl(p + 0x174C);
    constructor_camera_final_update(p + 0x1760);
    constructor_camera_collision_data(p + 0x17B0);
    func_000ECB78(p + 0x1800, a1);
    func_000ECB78(p + 0x1814, a1);
    F(0x1828) = zero;
    I(0x182C) = 0;
    func_000ECBA0(p);
    V(0x1880) = ZeroVector;
    V(0x1890) = ZeroPoint;
    V(0x18A0) = ZeroVector;
    V(0x18B0) = ZeroPoint;
    I(0x18C0) = 0;
    F(0x18C4) = zero;
    I(0x18C8) = 0;
}
#else
extern void func_000E6140(char *p, void *a1);
#endif
