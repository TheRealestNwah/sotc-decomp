typedef struct {
    int selected;
    int total;
    int cameras[5];
} CameraManager;

extern CameraManager B_0019FD20;
extern char B_0019FD40[];
extern void *GAMEUTIL_get_player_obj(void);
extern void *GAMEUTIL_get_boss_obj(void);
extern void doit_camera_lws_animation_manager(int, int, float);
extern void doit_camera_region_manager(void *, float);
extern void doit_cameraman(void *, float);
extern void reset_main_type_camera_lws_animation_update_flag(void);
extern int get_main_cameraman(void);
extern void *get_main_cameraman_camera_obj(void);
extern void gluUpdateCameraContext(void *);
extern void update_camera_context(void *, void *);

void doit_cameraman_manager(float time)
{
    int remaining;
    void *player;

    player = GAMEUTIL_get_player_obj();
    doit_camera_lws_animation_manager((int)player, (int)GAMEUTIL_get_boss_obj(), time);
    doit_camera_region_manager(GAMEUTIL_get_boss_obj(), time);
    for (remaining = 0; remaining < 5; ++remaining) {
        int camera = B_0019FD20.cameras[remaining];
        if (camera != 0) {
            doit_cameraman((void *)camera, time);
        }
    }
    reset_main_type_camera_lws_animation_update_flag();
    if (get_main_cameraman() != 0) {
        gluUpdateCameraContext(get_main_cameraman_camera_obj());
        update_camera_context(B_0019FD40, get_main_cameraman_camera_obj());
    }
}
