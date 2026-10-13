extern void reset_game_camera();

void end_jack_game_camera(int *arg0)
{
    *arg0 = 0;
    reset_game_camera();
}
