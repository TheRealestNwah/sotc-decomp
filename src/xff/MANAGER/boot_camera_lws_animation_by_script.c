extern char InitialGeometryPointer[];
extern int boot_camera_lws_animation(void *, void *, int, int, int, float);

int boot_camera_lws_animation_by_script(void *anim)
{
    return boot_camera_lws_animation(anim, InitialGeometryPointer, 0, 0, 0, 0.0f);
}
