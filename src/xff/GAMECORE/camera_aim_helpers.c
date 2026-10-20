typedef struct {
    int target;
    int a;
    int b;
    float c;
    int d;
    float max;
    float min;
    int e;
    int f;
    char interp[1];
} AimRot;
extern void GAMEUTIL_reset_interp_ratio_cntrl(int *);
static void func_000E1650(void *);
static float func_000E15F8(float value, float limit)
{
    if (limit <= value)
        return 1.0f;
    return value / limit;
}
static void func_000E1620(AimRot *object)
{
    func_000E1650(object);
    object->f = 0;
    GAMEUTIL_reset_interp_ratio_cntrl((int *)object->interp);
}
static void func_000E1650(void *object)
{
    *(int *)((char *)object + 4) = 0;
}

extern int CAM_is_inside_of_region_aim_angle_rot(float *, float *, int *, float, float, float);
static void func_000E1788(AimRot *, int, float, float);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern float GAMEUTIL_get_difference_pitch_and_pitch(float, float);
static int func_000E1658(AimRot *object, float from, float aim, float high, float low)
{
    if (object->a == 0) {
        if (high - low < 0.034906585f)
            high = low + 0.034906585f;
        if (!CAM_is_inside_of_region_aim_angle_rot(0, 0, &object->target, from, aim, high)) {
            func_000E1788(object, 1, from, aim);
            return 1;
        }
    }
    return 0;
}
static float func_000E16F0(AimRot *object, float a, float b, float center)
{
    float da, db;
    if (object->target == 0) {
        da = GAMEUTIL_get_difference_yaw_and_yaw(center, a);
        db = GAMEUTIL_get_difference_yaw_and_yaw(center, b);
    } else {
        da = GAMEUTIL_get_difference_pitch_and_pitch(center, a);
        db = GAMEUTIL_get_difference_pitch_and_pitch(center, b);
    }
    return da < db ? a : b;
}

extern int GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(float *, float, float, float);
static void func_000E1788(AimRot *object, int force, float from, float aim)
{
    if (object->target == 1 || object->d == 1) {
        object->a = 1;
    } else if (object->a == 1 || force) {
        int direction = GAMEUTIL_inc_or_dec_for_near_to_aim_yaw(0, from, 1.0f, aim);
        if (direction == 1)
            object->a = 2;
        else if (direction == -1)
            object->a = 3;
        else
            object->a = 0;
    }
}

typedef struct {
    int words[0x37];
} CameraParameter;
extern float CAM_get_motion_kind_interp_ratio_target(char *);
static void func_000E1890(CameraParameter *, char *, CameraParameter *, CameraParameter *, float);
static void func_000E1820(char *object)
{
    if (*(int *)(object + 0x1E8)) {
        float ratio = CAM_get_motion_kind_interp_ratio_target(object);
        if (*(int *)(object + 0x28))
            func_000E1890((CameraParameter *)(object + 0x10C), object,
                         (CameraParameter *)(object + 0x2C),
                         (CameraParameter *)(object + 0x1EC), ratio);
        else
            func_000E1890((CameraParameter *)(object + 0x10C), object, 0,
                         (CameraParameter *)(object + 0x1EC), ratio);
        *(int *)(object + 0x108) = 1;
    } else
        *(int *)(object + 0x108) = 0;
}
static void func_000E1890(CameraParameter *output, char *camera,
                          CameraParameter *previous, CameraParameter *current, float ratio)
{
    *output = *current;
}

extern float GAMEUTIL_doit_interp_ratio_cntrl(void *, float);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
static float func_000E22C0(char *control, void *camera, float delta)
{
    if (*(int *)((char *)camera + 0x564) != 0)
        delta = -delta;
    return GAMEUTIL_doit_interp_ratio_cntrl(control, delta);
}
static float func_000E22E0(char *control, void *camera, float delta)
{
    if (*(int *)((char *)camera + 0x1360) != 1)
        delta = -delta;
    return GAMEUTIL_doit_interp_ratio_cntrl(control + 0x20, delta);
}
static float func_000E2308(char *control, void *camera, float delta)
{
    if (*(int *)((char *)camera + 0x3B0) >= 0)
        delta = -delta;
    return GAMEUTIL_doit_interp_ratio_cntrl(control + 0x40, delta);
}
static float func_000E2330(void *object, void *unused)
{
    char *camera = object;
    char *definition = *(char **)camera;
    return GAMEUTIL_get_dist_ratio(*(float *)(camera + 0x1A0), 0.0f,
                                  *(float *)(definition + 0x150));
}

extern float GAMEUTIL_get_hope_value_interp_value_cntrl(void *);
extern void GAMEUTIL_reset_interp_ratio_cntrl(int *);
extern void GAMEUTIL_set_param_interp_ratio_cntrl(char *, float, float);
extern float GAMEUTIL_doit_interp_ratio_cntrl(void *, float);
extern float GAMEUTIL_doit_interp_value_cntrl(void *, void *, float);
static float func_000E2358(char *ratio, void *value, float target, float delta)
{
    if (GAMEUTIL_get_hope_value_interp_value_cntrl(value) != target) {
        GAMEUTIL_reset_interp_ratio_cntrl((int *)ratio);
        GAMEUTIL_set_param_interp_ratio_cntrl(ratio, 0.0f, 1.0f);
    }
    GAMEUTIL_doit_interp_ratio_cntrl(ratio, delta);
    return GAMEUTIL_doit_interp_value_cntrl(value, ratio, target);
}
