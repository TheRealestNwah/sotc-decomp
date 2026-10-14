extern void GAMEUTIL_reset_status_manager(void *, int);
extern void GAMEUTIL_constructor_position_filter(void *);
extern void CAM_init_aim_angle_rot(void *, int);

void constructor_camera_target_approach(char *p)
{
    GAMEUTIL_reset_status_manager(p, 0);
    GAMEUTIL_constructor_position_filter(p + 0x10);
    *(int *)(p + 0x40) = 0;
    CAM_init_aim_angle_rot(p + 0x44, 1);
}
