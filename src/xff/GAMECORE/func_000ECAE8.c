extern void func_000E97A0(char *, char *);
extern void CAM_init_camera_warp_cntrl(char *, int, int, int);

static void func_000ECAE8(char *self, char *other)
{
    *(int *)(other + 0x80) = 0;
    *(int *)(other + 0x260) = 0;
    func_000E97A0(other, self);
    CAM_init_camera_warp_cntrl(self + 0x1840, 0, 0, 0);
}
