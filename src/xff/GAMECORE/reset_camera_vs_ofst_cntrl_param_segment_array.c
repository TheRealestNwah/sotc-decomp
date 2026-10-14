extern char B_0019FCF8[];
extern void *memset(void *, int, unsigned int);

void reset_camera_vs_ofst_cntrl_param_segment_array(void)
{
    memset(B_0019FCF8, 0, 0x28);
}
