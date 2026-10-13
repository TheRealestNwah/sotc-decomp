void begin_time_interp_camera_dist_to_look_at(void *arg0, float fparg0, float fparg1)
{
    (*(float *)((char *)(arg0) + 0x78)) = fparg1;
    (*(float *)((char *)(arg0) + 0x70)) = fparg0;
    (*(int *)((char *)(arg0) + 0x74)) = 0;
}
