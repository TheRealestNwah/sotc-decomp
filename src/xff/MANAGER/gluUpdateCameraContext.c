extern void *get_cur_camera_context(void);
extern void *D_00130480;

void gluUpdateCameraContext(void)
{
    D_00130480 = get_cur_camera_context();
}
