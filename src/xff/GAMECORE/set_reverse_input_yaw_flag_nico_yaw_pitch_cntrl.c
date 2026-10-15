extern void *memset(void *, int, unsigned int);

void set_reverse_input_yaw_flag_nico_yaw_pitch_cntrl(int *c, int flag)
{
    if (*(int *)((char *)c + 0x130) != flag) {
        c[0] = 0;
        memset(c + 1, 0, 0x28);
        *(int *)((char *)c + 0x130) = flag;
    }
}
