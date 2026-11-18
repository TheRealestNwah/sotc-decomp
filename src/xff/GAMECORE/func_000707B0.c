/* Sets the camera spring target from the base yaw and pitch (resetting the spring unless mode is 2, else storing the target directly), steps it, then moves the base yaw (when flag is 1) and pitch toward it. The pinned `two` in a2 is reused for the compare and the call argument; the target copy goes through two 64-bit halves pinned to v1 and v0, as in the Original. */
extern struct { char pad[0x180]; float f; } gcGlobalVar;
extern float get_base_yaw_nico_yaw_pitch_cntrl(void *);
extern float get_base_pitch_nico_yaw_pitch_cntrl(void *);
extern void update_base_yaw_nico_yaw_pitch_cntrl(void *, float);
extern void update_base_pitch_nico_yaw_pitch_cntrl(void *, float);
extern void reset_double_spring_interp_cntrl3D(void *, void *, int);
extern void doit_double_spring_interp_cntrl3D(void *, void *, int, float);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern float GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(float, float);

typedef union { float f[4]; long l[2]; } Vec4f;
typedef int s128 __attribute__((mode(TI)));

static void func_000707B0(char *obj, int mode, int flag)
{
    Vec4f v, src;
    register int two __asm__("$6");
    src.f[0] = get_base_yaw_nico_yaw_pitch_cntrl(obj + 0xC);
    src.f[1] = get_base_pitch_nico_yaw_pitch_cntrl(obj + 0xC);
    src.f[2] = 0;
    src.f[3] = 0;
    two = 2;
    { register long a asm("$3") = src.l[0]; register long b asm("$2") = src.l[1]; v.l[0] = a; v.l[1] = b; }
    if (mode != two) {
        reset_double_spring_interp_cntrl3D(obj + 0x160, &v, two);
    } else {
        *(s128 *)(obj + 0x190) = *(s128 *)&v;
    }
    doit_double_spring_interp_cntrl3D(obj + 0x160, obj + 0x150, 0, gcGlobalVar.f);
    if (flag == 1) {
        update_base_yaw_nico_yaw_pitch_cntrl(obj + 0xC, GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(get_base_yaw_nico_yaw_pitch_cntrl(obj + 0xC), *(float *)(obj + 0x190)));
    }
    update_base_pitch_nico_yaw_pitch_cntrl(obj + 0xC, GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(get_base_pitch_nico_yaw_pitch_cntrl(obj + 0xC), *(float *)(obj + 0x194)));
}
