extern void GAMEUTIL_constructor_interp_ratio_cntrl(void *);
extern void GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(void *, int);
extern void GAMEUTIL_reset_look_at_vs_offset(void *);

void GAMEUTIL_constructor_look_at_vs_offset(char *o)
{
    *(int *)(o + 0x18) = 0;
    GAMEUTIL_constructor_interp_ratio_cntrl(o + 0x1C);
    GAMEUTIL_set_act_max_zero_clip_flag_interp_ratio_cntrl(o + 0x1C, 1);
    *(float *)(o + 0x3C) = 0.17453293f;
    *(float *)(o + 0x40) = 0.17453293f;
    *(float *)(o + 0x44) = 0.69813170f;
    *(float *)(o + 0x48) = 0.8f;
    *(float *)(o + 0x4C) = 1.45f;
    *(float *)(o + 0x50) = 0.61086523f;
    *(int *)(o + 0x0) = 0;
    GAMEUTIL_reset_look_at_vs_offset(o);
}
