extern int get_main_cameraman();
extern int get_game_camera();
extern int reset_game_camera_standby_flag();

int ResetCamFinalizer(void)
{
    return reset_game_camera_standby_flag(get_game_camera(get_main_cameraman()));
}
