int CAM_is_visible_now_target_visibility(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x44)) == 0;
}
