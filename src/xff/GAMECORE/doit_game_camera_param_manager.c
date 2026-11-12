extern void func_000ED678(int *, int *);
extern void func_000EEA28(int *, int, int, int);
extern void func_000EED00(int *, int *, int *, int, float, float);
extern int func_000F2700(int *, int *);
extern void func_000F27A0(void *, int, int, int, float);
extern void func_000F2970(void *, int *, int);
extern void func_000F29C0(void *);
extern void func_000F2A40(int);
extern float get_interp_ratio_game_camera_param_manager(void *);
extern float get_interp_time_game_camera_param_manager(void *);
extern int is_reset_or_lws_movie_or_cutout_game_camera(int);

#ifdef NONMATCHING /* 82 diffs: call sequence, pointer pins ($s0 cp, $s2 cur, $s3 sel, $s4 prev, $s5/$s6 args) and control flow right; the compiler hoists the m+0x664 address above the first calls and loads *cp through it, the original keeps base+offset loads */
void doit_game_camera_param_manager(char *m, int a10, int a2, int a30, float dt)
{
    register int a1 __asm__("$22") = a10;
    register int a3 __asm__("$21") = a30;
    int sp0;
    float r;
    float inv;
    register int *cur __asm__("$18");
    register int *prev __asm__("$20");
    register int *sel __asm__("$19");
    register int *cp __asm__("$16");
    float t;

    cur = (int *)(m + 0x10);
    prev = (int *)(m + 0xCB8);
    sp0 = 0;
    func_000F2970(m + 0x130C, &sp0, a1);
    func_000F27A0(m, *(int *)(m + 0x664), sp0, a2, dt);
    cp = (int *)(m + 0x664);
    sel = cp;
    if (sp0 != *(int *)(m + 0x664)) {
        func_000ED678(cur, prev);
        *(int *)m = 1;
        *(int *)(m + 0x664) = sp0;
    } else {
        *(int *)m = 0;
        cur = (int *)(m + 0x10);
        prev = (int *)(m + 0xCB8);
    }
    func_000EEA28(cp, sp0, a1, a3);
    if (is_reset_or_lws_movie_or_cutout_game_camera(a3) == 1) {
        t = get_interp_time_game_camera_param_manager(m);
        *(float *)(m + 4) = t;
    } else if (*(int *)m != 1) {
        *(float *)(m + 4) = *(float *)(m + 4) + dt;
    } else {
        *(float *)(m + 4) = 0.0f;
    }
    r = get_interp_ratio_game_camera_param_manager(m);
    inv = 1.0f - r;
    sel = *cur != 0 ? cur : cp;
    func_000ED678(prev, cp);
    func_000EED00(prev, sel, cp, func_000F2700(cp, sel), inv, r);
    func_000F29C0(m);
    func_000F2A40(a1);
}
#endif
