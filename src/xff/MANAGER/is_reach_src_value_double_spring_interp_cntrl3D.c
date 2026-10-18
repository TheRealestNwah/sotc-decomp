extern float GAMEUTIL_get_difference_value(int, float, float);
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
int is_reach_src_value_double_spring_interp_cntrl3D(void *control, float *target)
{
    char *state = control;
    int *mode = (int *)(state + 0x14);
    float *value = (float *)(state + 0x30);
    int i = 0;
    int reached = 1;
    do {
        float a = *value++;
        float b = *target++;
        int m = *mode++;
        float difference = GAMEUTIL_get_difference_value(m, a, b);
        if (!GAMEUTIL_is_nearly_equal_zero(difference, *(float *)(state + 0x10) * 3.0f)) {
            reached = 0;
            break;
        }
    } while (++i < 3);
    return reached;
}
