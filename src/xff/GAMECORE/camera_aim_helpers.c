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
