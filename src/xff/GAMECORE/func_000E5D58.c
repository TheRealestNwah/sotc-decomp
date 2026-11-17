extern char *get_game_camera(int);
extern void CAM_reset_mode_ratio_follow_rot(void *, int, void *);
extern float D_0017B720;

extern void func_000EC420(void *, void *, int);
extern void func_000EC428(void *, void *, int);
extern void func_000EC470(void *, void *, int);
extern void func_000EC480(void *, void *, int);
extern void func_000EC488(void *, void *, int);
extern void func_000EC490(void *, void *, int);
extern void func_000EC538(void *, void *, int);
extern void func_000EC540(void *, void *, int);
extern void func_000EC5E8(void *, void *, int);
extern void func_000EC690(void *, void *, int);
extern void func_000EC740(void *, void *, int);
extern void func_000EC7B0(void *, void *, int);
extern void func_000EC828(void *, void *, int);
extern void func_000EC8C8(void *, void *, int);
extern void func_000EC9E0(void *, void *, int);
extern void func_000E8F08(void *, void *, int);
extern void func_000ECAE8(void *, void *, int);
extern void func_000ECB30(void *, void *, int);

static void func_000E5D58(char *p, int mgr)
{
    char *cam = get_game_camera(mgr);
    char *s = p + 0x1370;

    if (*(int *)(cam + 0x1360) != *(int *)(cam + 0x1364)) {
    switch (*(int *)(p + 0x1364)) {
    case 0: func_000EC420(s, p, mgr); break;
    case 1: func_000EC428(s, p + 0x2C44, mgr); break;
    case 2: func_000EC470(s, p + 0x2D20, mgr); break;
    case 3: func_000EC480(s, p + 0x2DE0, mgr); break;
    case 4: func_000EC488(s, p + 0x2ED0, mgr); break;
    case 5: func_000EC490(s, p + 0x2FF0, mgr); break;
    case 6: func_000EC538(s, p + 0x3120, mgr); break;
    case 7: func_000EC540(s, p + 0x3270, mgr); break;
    case 8: func_000EC5E8(s, p + 0x34E0, mgr); break;
    }
    CAM_reset_mode_ratio_follow_rot(s + 0x14A0, *(int *)(p + 0x1364), p);
    *(int *)(s + 0x228) = 0;
    *(float *)(s + 0x22C) = *(float *)(s + 0x234);
    *(float *)(s + 0x230) = *(float *)(s + 0x238);
    __asm__ __volatile__("" ::: "memory");
    switch (*(int *)(p + 0x1360)) {
    case 0: func_000EC690(s, p, mgr); return;
    case 1: func_000EC740(s, p + 0x2C44, mgr); return;
    case 2: func_000EC7B0(s, p + 0x2D20, mgr); return;
    case 3: func_000EC828(s, p + 0x2DE0, mgr); return;
    case 4: func_000EC8C8(s, p + 0x2ED0, mgr); return;
    case 5: func_000EC9E0(s, p + 0x2FF0, mgr); return;
    case 6: func_000E8F08(s, p + 0x3120, mgr); return;
    case 7: func_000ECAE8(s, p + 0x3270, mgr); return;
    case 8: func_000ECB30(s, p + 0x34E0, mgr); return;
    }
    } else {
        *(float *)(s + 0x228) += D_0017B720;
    }
}

