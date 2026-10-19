extern void *get_cur_camera_context(void);

void *iosgluGetCameraContext(void)
{
    return get_cur_camera_context();
}
