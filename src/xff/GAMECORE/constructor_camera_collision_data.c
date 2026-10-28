extern int reset_camera_collision_data_except_slide_move_ratio(int *);

void constructor_camera_collision_data(void *arg0)
{
    reset_camera_collision_data_except_slide_move_ratio((int *)arg0);
    (*(float *)((char *)(arg0) + 0x40)) = -1.0f;
    (*(float *)((char *)(arg0) + 0x44)) = 1.0f;
}
