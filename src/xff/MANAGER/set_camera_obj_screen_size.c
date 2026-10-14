extern int set_screen_size();

int set_camera_obj_screen_size(char *p, int a, int b)
{
    return set_screen_size(*(int *)(p + 0x250), a, b);
}
