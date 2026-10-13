extern int get_cur_camera_context();
extern int D_00130480;

void gluUpdateCameraContext(void)
{
    D_00130480 = get_cur_camera_context();
}
