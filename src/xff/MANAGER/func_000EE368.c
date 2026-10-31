extern void stop_camera_lws_animation_callback(int);
extern void end_camera_lws_animation(int);
extern void stop_camera_lws_animation_geometry_pointer_reference(int);

static void func_000EE368(void *obj, int *work)
{
    stop_camera_lws_animation_callback(*work);
    end_camera_lws_animation(*work);
    stop_camera_lws_animation_geometry_pointer_reference(*work);
}
