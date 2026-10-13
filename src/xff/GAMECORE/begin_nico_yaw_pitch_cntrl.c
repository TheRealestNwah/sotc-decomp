extern void GAMEUTIL_begin_move_angle(void *);
extern void func_0000DAF0();

void begin_nico_yaw_pitch_cntrl(void *arg0, float fparg0, float fparg1)
{
    func_0000DAF0();
    (*(int *)((char *)(arg0) + 0x2C)) = 1;
    (*(float *)((char *)(arg0) + 0x40)) = (float) (*(float *)((char *)(arg0) + 0x7C));
    (*(float *)((char *)(arg0) + 0x50)) = (float) (*(float *)((char *)(arg0) + 0xA4));
    (*(float *)((char *)(arg0) + 0x5C)) = fparg0;
    (*(float *)((char *)(arg0) + 0x68)) = fparg1;
    (*(int *)((char *)(arg0) + 0x30)) = 0;
    (*(int *)((char *)(arg0) + 0x38)) = 0;
    (*(int *)((char *)(arg0) + 0x34)) = 0;
    (*(int *)((char *)(arg0) + 0x3C)) = 0;
    (*(int *)((char *)(arg0) + 0x48)) = 0;
    (*(int *)((char *)(arg0) + 0x44)) = 0;
    (*(int *)((char *)(arg0) + 0x4C)) = 0;
    (*(int *)((char *)(arg0) + 0x54)) = 0;
    (*(int *)((char *)(arg0) + 0x58)) = 0;
    (*(int *)((char *)(arg0) + 0x60)) = 0;
    (*(int *)((char *)(arg0) + 0x64)) = 0;
    GAMEUTIL_begin_move_angle(arg0 + 0x88);
    GAMEUTIL_begin_move_angle(arg0 + 0xB0);
}
