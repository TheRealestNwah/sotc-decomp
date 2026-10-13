void GAMEUTIL_convert_from_lw_to_game_coord(void *arg0)
{
    (*(float *)((char *)(arg0) + 0)) = (float) -(*(float *)((char *)(arg0) + 0));
    (*(float *)((char *)(arg0) + 8)) = (float) -(*(float *)((char *)(arg0) + 8));
}
