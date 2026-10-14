extern void end_camera_lws_animation_by_paramID(int);
extern int get_boss_subjective_camera_lws_animation_param();

void end_check_and_boot_boss_subjective_camera_lws_animation(void)
{
    int temp_v0;

    temp_v0 = get_boss_subjective_camera_lws_animation_param();
    if (temp_v0 != 0) {
        end_camera_lws_animation_by_paramID(temp_v0);
    }
}
