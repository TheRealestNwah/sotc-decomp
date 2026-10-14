extern int get_main_type_camera_lws_animation();
extern int D_00139F40;

int is_main_type_camera_lws_animation_update(void)
{
    if (get_main_type_camera_lws_animation() == 0) {
        D_00139F40 = 0;
    }
    return D_00139F40;
}
