extern void func_000EC420(void *, void *, int);
extern void func_000EC428(void *, void *, int);
extern void func_000EC470(void *, void *, int);
extern void func_000EC480(void *, void *, int);
extern void func_000EC488(void *, void *, int);
extern void func_000EC490(void *, void *, int);
extern void func_000EC538(void *, void *, int);
extern void CAM_init_camera_warp_cntrl(void *, int, int, int);
static void func_000EC690(char *self, char *c, int mgr)
{
    func_000EC420(self, c, mgr);
    func_000EC428(self, c + 0x2C44, mgr);
    func_000EC470(self, c + 0x2D20, mgr);
    func_000EC480(self, c + 0x2DE0, mgr);
    func_000EC488(self, c + 0x2ED0, mgr);
    func_000EC490(self, c + 0x2FF0, mgr);
    func_000EC538(self, c + 0x3120, mgr);
    CAM_init_camera_warp_cntrl(self + 0x1840, 0, 0, 0);
}
