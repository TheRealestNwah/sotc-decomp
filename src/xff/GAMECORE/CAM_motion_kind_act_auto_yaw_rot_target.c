int CAM_motion_kind_act_auto_yaw_rot_target(void *arg0)
{
    return ((unsigned int) (*(unsigned int *)((char *)(arg0) + 0x174)) >> 0x1D) & 1;
}
