typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; int i[4]; } Vec4;

void reset_time_interp_param_camera_dist_to_look_at(char *pa0)
{
    *(float *)(pa0 + 0x78) = 1.0f;
    *(int *)(pa0 + 0x74) = 0;
    *(int *)(pa0 + 0x70) = 0;
}
