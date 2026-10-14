float get_rewind_begin_dist_to_target_camera_dist_to_look_at(void *arg0, float fparg0)
{
    float var_f0;

    var_f0 = fparg0;
    if (((*(int *)((char *)(arg0) + 0x30)) ^ 2) == 0) {
        var_f0 = (*(float *)((char *)(arg0) + 0x38));
    }
    return var_f0;
}
