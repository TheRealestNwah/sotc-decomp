extern void GAMEUTIL_constructor_interp_ratio_cntrl(char *);
extern void GAMEUTIL_init_record_info(char *, int, int, void *, int);

void CAM_constructor_target(char *t, void *a)
{
    *(int *)(t + 0) = 0;
    *(int *)(t + 4) = 0;
    GAMEUTIL_constructor_interp_ratio_cntrl(t + 8);
    *(int *)(t + 0x28) = 0;
    *(int *)(t + 0x108) = 0;
    *(int *)(t + 0x1E8) = 0;
    *(int *)(t + 0x2C8) = 0;
    GAMEUTIL_init_record_info(t + 0x2CC, 4, 30, a, 0);
}
