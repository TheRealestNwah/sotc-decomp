extern void *DebugFindPlayer(int);

int change_to_player_camera_target(int *p)
{
    void *pl = DebugFindPlayer(p[2]);
    if (pl == 0)
        return 0;
    p[7] = (int)pl;
    return 1;
}
