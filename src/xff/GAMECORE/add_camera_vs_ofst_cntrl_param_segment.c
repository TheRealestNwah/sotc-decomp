extern void *B_0019FCF8[];

void add_camera_vs_ofst_cntrl_param_segment(void *p)
{
    int i;
    for (i = 0; i < 10; i++) {
        if (B_0019FCF8[i] == 0) {
            B_0019FCF8[i] = p;
            return;
        }
    }
    __asm__ __volatile__("break 0");
}
