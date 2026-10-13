int CAM_motion_kind_is_mode_lock_target(void *arg0)
{
    return ((unsigned int) (*(unsigned int *)((char *)(arg0) + 0x178)) >> 5) & 1;
}
