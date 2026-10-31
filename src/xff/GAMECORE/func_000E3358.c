typedef int s128 __attribute__((mode(TI)));
extern s128 *get_camera_position(void *);
extern s128 *get_camera_direction(void *);
extern s128 *get_camera_up_direction(void *);
extern void doit_game_camera(void *, void *, float);

static void func_000E3358(void **o, float f)
{
    void *cam = *o;
    s128 v[3];

    v[0] = *get_camera_position(cam);
    v[1] = *get_camera_direction(cam);
    v[2] = *get_camera_up_direction(cam);
    doit_game_camera(o + 8, o, f);
}
