void set_param_double_spring_interp_common(char *p, float f1, float f2, float f3, float f4)
{
    *(float *)(p + 0x0) = f1;
    *(float *)(p + 0x4) = f2;
    *(float *)(p + 0x8) = f3;
    *(float *)(p + 0xC) = f4;
}
