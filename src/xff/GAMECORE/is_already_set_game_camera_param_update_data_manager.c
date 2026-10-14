int is_already_set_game_camera_param_update_data_manager(void *arg0, int arg1)
{
    return (*(int *)((char *)(((arg1 * 0x65C) + (*(int *)((char *)(arg0) + 4)))) + 4)) != 0;
}
