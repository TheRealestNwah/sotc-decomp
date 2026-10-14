extern void reset_camera_target_visible_angle_manager(void *);
extern void set_parameter_camera_target_visible_angle_manager(void *, int, float, float);

void constructor_camera_target_visible_angle_manager(void *p)
{
    reset_camera_target_visible_angle_manager(p);
    set_parameter_camera_target_visible_angle_manager(p, 0xF, 180.0f, 2.0f);
}
