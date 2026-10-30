extern void doit_aim_angle_interp_cntrl(void *, float, float, void *, float);

static void func_000D70B8(char *cam, void *unused, void *arg, float yaw, float pitch, float rate)
{
    *(float *)(cam + 0x350) = yaw;
    *(float *)(cam + 0x354) = pitch;
    doit_aim_angle_interp_cntrl(cam + 0x358, yaw, 0, arg, rate);
    doit_aim_angle_interp_cntrl(cam + 0x368, pitch, 0, arg, rate);
}
