extern float D_0017B720;
extern int GAMEUTIL_is_boss_booting(void);
extern void func_000E4C48(int *, void *);
extern void doit_camera_pause_rise(void *, int *, void *);
extern int is_end_camera_pause_rise(void *);

void doit_game_camera(int *g, void *arg, float dt)
{
    D_0017B720 = dt;
    if (GAMEUTIL_is_boss_booting() == 0)
        g[0x3110 / 4] = 0;
    switch ((unsigned int)g[0]) {
    case 1:
        break;
    case 0:
        func_000E4C48(g, arg);
        return;
    case 2:
        doit_camera_pause_rise((char *)g + 0x3750, g, arg);
        if (is_end_camera_pause_rise((char *)g + 0x3750) == 1)
            g[0] = 0;
        break;
    }
}
