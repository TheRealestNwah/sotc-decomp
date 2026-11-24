#ifdef NONMATCHING
/* Parked: 9 diffs, same size. Runs the two camera sub-updates, then resets or updates the visible-angle manager at o+0x390 depending on mode. Pinning o to $20 gives the Original register allocation (o s4, a s1, b s3, c s2). Remaining: the Original sets up all manager arguments once before the mode branch, but here the doit path sets a1-a3 again; a 30-minute permuter run found only semantics-changing variants. */
extern void func_000D70B8(char *cam, void *unused, int arg, float yaw, float pitch, float rate);
extern void func_000D7138(char *cam, void *a, void *c, int mode, float rate);
extern void doit_camera_target_visible_angle_manager(void *mgr, void *a, void *b, void *c, float rate);
extern void reset_camera_target_visible_angle_manager(void *mgr, void *a, void *b, void *c, float rate);

static void func_000D6F28(char *o_, void *a_, void *b_, void *c_, int mode, float yaw, float pitch, float rate)
{
    register char *o __asm__("$20") = o_;
    void *a = a_;
    void *b = b_;
    void *c = c_;
    func_000D70B8(o, b, mode, yaw, pitch, rate);
    func_000D7138(o, a, c, mode, rate);
    if (mode == 1) {
        reset_camera_target_visible_angle_manager(o + 0x390, a, b, c, rate);
        return;
    }
    doit_camera_target_visible_angle_manager(o + 0x390, a, b, c, rate);
}
#endif
