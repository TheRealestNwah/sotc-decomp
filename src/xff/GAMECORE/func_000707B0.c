/* Parked: 47 differing words; the original sets the constant 2 once and reuses it for the compare and the call argument. */
#ifdef NONMATCHING
extern struct { char pad[0x180]; float f; } gcGlobalVar;
extern float get_base_yaw_nico_yaw_pitch_cntrl(void *);
extern float get_base_pitch_nico_yaw_pitch_cntrl(void *);
extern void update_base_yaw_nico_yaw_pitch_cntrl(void *, float);
extern void update_base_pitch_nico_yaw_pitch_cntrl(void *, float);
extern void reset_double_spring_interp_cntrl3D(void *, void *, int);
extern void doit_double_spring_interp_cntrl3D(void *, void *, int, float);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern float GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(float, float);

typedef struct { float f[4]; } __attribute__((aligned(8))) Vec4f;
typedef int s128 __attribute__((mode(TI)));

static void func_000707B0(char *obj, int mode, int flag)
{
    Vec4f v, src;
    src.f[0] = get_base_yaw_nico_yaw_pitch_cntrl(obj + 0xC);
    src.f[1] = get_base_pitch_nico_yaw_pitch_cntrl(obj + 0xC);
    src.f[2] = 0;
    src.f[3] = 0;
    v = src;
    if (mode != 2) {
        reset_double_spring_interp_cntrl3D(obj + 0x160, &v, 2);
    } else {
        *(s128 *)(obj + 0x190) = *(s128 *)&v;
    }
    doit_double_spring_interp_cntrl3D(obj + 0x160, obj + 0x150, 0, gcGlobalVar.f);
    if (flag == 1) {
        update_base_yaw_nico_yaw_pitch_cntrl(obj + 0xC, GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(get_base_yaw_nico_yaw_pitch_cntrl(obj + 0xC), *(float *)(obj + 0x190)));
    }
    update_base_pitch_nico_yaw_pitch_cntrl(obj + 0xC, GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(get_base_pitch_nico_yaw_pitch_cntrl(obj + 0xC), *(float *)(obj + 0x194)));
}
#endif
