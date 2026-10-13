void GAMEUTIL_forward_timer_still_one_ratio_time_interp_ratio_cntrl(void *arg0)
{
    (*(float *)((char *)(arg0) + 0xC)) = (float) ((*(float *)((char *)(arg0) + 0x14)) + (*(float *)((char *)(arg0) + 0x18)));
}
