extern float YUnitVector[];
extern void *GAMEUTIL_get_riding_horse_object(void *);
/* Declared with the float before the axis: same registers as the real
   (void *, float *, float), but only this order sets them up as the original does. */
extern void GAMEUTIL_act_axis_rot_root_quaternion_abs(void *, float, float *);

static void func_00070710(void **o, float ang)
{
    void *h = GAMEUTIL_get_riding_horse_object(o[1]);

    GAMEUTIL_act_axis_rot_root_quaternion_abs(h != 0 ? h : o[1], ang, YUnitVector);
}
