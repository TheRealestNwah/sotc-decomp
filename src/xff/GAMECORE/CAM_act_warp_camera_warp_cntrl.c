typedef struct {
    int x0;
    int x4;
    float x8;
    int xC;
    float x10;
    int x14[3];
    float x20;
    int x24;
    int x28;
    int x2C;
    float x30;
    float x34;
    float x38;
    float x3C;
} WarpCntrl;

extern char *get_game_camera(int manager);

static inline void reset_warp(WarpCntrl *w)
{
    w->x4 = 0;
    *(int *)&w->x8 = 0;
    *(int *)&w->x10 = 0;
    *(int *)&w->x20 = 0;
    w->x24 = 0;
    w->x28 = 0;
    w->x2C = 0;
    w->x30 = w->x34 = w->x38 = 3.4028235e38f;
    w->x3C = 1.0f;
}

int CAM_act_warp_camera_warp_cntrl(WarpCntrl *w, float x, float y, int unused, int manager)
{
    if (*(int *)(get_game_camera(manager) + 0x40) == 0) {
        if ((0.0f < x && x <= w->x8) || (0.0f < y && y <= w->x10) || 0.0001f <= w->x20 || w->x28 == 1) {
            reset_warp(w);
            return 1;
        }
    }
    return 0;

}
