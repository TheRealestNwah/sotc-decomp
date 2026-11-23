/* Parked attempt, 6 diffs, same size. Copies self+0xD0/D4 into a 16-byte vector for reset_double_spring_interp_cntrl3D after aim/warp init. Remaining: the Original hoists the t.z zero store above the first call's argument setup and the float loads. */
#ifdef NONMATCHING
typedef struct { float x, y; int z; float w; } __attribute__((aligned(8))) V;
extern void CAM_init_aim_angle_rot(char *, int);
extern void CAM_init_camera_warp_cntrl(char *, int, int, int);
extern void reset_double_spring_interp_cntrl3D(char *, V *);
static void func_000EC828(char *self, char *c)
{
    V v;
    V t;
    char *a = c + 0x4;

    t.x = *(float *)(self + 0xD0);
    t.y = *(float *)(self + 0xD4);
    t.z = 0;
    t.w = 0.0f;
    v = t;
    CAM_init_aim_angle_rot(a, 0);
    CAM_init_aim_angle_rot(c + 0x48, 1);
    *(int *)(a + 0x88) = 0;
    *(int *)(a + 0x8C) = 0;
    CAM_init_camera_warp_cntrl(self + 0x1840, 2, 3, 0);
    reset_double_spring_interp_cntrl3D(c + 0xA0, &v);
}
#endif
