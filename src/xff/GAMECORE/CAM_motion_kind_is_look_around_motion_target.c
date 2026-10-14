int CAM_motion_kind_is_look_around_motion_target(void *arg0)
{
    return ((unsigned int) (*(unsigned int *)((char *)(arg0) + 0x174)) >> 0x1C) & 1;
}
