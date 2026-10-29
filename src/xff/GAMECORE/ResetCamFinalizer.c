extern int get_main_cameraman(void);
extern int get_game_camera(int);
extern void reset_game_camera_standby_flag(void *);

void ResetCamFinalizer(void)
{
    reset_game_camera_standby_flag((void *)get_game_camera(get_main_cameraman()));
}
