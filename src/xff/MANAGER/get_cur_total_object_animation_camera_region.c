extern int B_0015E350[];
int get_cur_total_object_animation_camera_region(void)
{
    int n = 0;
    int i;
    int *p = B_0015E350;
    for (i = 49; i >= 0; i--) {
        if (*p++ != 0)
            n++;
    }
    return n;
}
