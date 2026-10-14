extern void *get_clip_screen(void *);
extern void set_camera_position(void *, void *);
extern void set_camera_direction(void *, void *);
extern void set_camera_up_direction(void *, void *);
extern void set_view_angle(void *, float);

void set_camera_parameter_cameraman(void **manager, void *position, void *direction, void *up, float angle)
{
    set_camera_position(*manager, position);
    set_camera_direction(*manager, direction);
    set_camera_up_direction(*manager, up);
    set_view_angle(get_clip_screen(*manager), angle);
}
