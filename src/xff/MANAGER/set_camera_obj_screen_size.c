extern void set_screen_size(void *, int, int);

void set_camera_obj_screen_size(char *camera, int width, int height)
{
    set_screen_size(*(void **)(camera + 0x250), width, height);
}
