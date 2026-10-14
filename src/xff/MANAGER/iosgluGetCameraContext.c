extern int get_cur_camera_context();

int iosgluGetCameraContext(int a, int b, int c, int d)
{
    return get_cur_camera_context(a, b, c, d);
}
