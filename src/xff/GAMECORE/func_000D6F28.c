#ifdef NONMATCHING
/* Parked: 25 words differ (register allocation: original keeps o in s4, a in s1, b in s3, c in s2) */
extern void func_000D70B8(char *cam, void *unused, int arg, float yaw, float pitch, float rate);
extern void func_000D7138(char *cam, void *a, void *c, int mode, float rate);
extern void doit_camera_target_visible_angle_manager(void *mgr, void *a, void *b, void *c, float rate);
extern void reset_camera_target_visible_angle_manager(void *mgr, void *a, void *b, void *c, float rate);

static void func_000D6F28(char *o, void *a, void *b, void *c, int mode, float yaw, float pitch, float rate)
{
    char *m;
    func_000D70B8(o, b, mode, yaw, pitch, rate);
    func_000D7138(o, a, c, mode, rate);
    m = o + 0x390;
    if (mode == 1) {
        reset_camera_target_visible_angle_manager(m, a, b, c, rate);
        return;
    }
    doit_camera_target_visible_angle_manager(m, a, b, c, rate);
}
#endif
