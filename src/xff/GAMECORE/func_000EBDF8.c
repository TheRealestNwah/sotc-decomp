extern float D_0017B720;
extern void constructor_game_camera_param_update_data_manager(void *);
extern void func_000E5268(void *, void *, void *, void *, void *);
extern void doit_game_camera_param_manager(void *, void *, void *, void *, float);
extern void get_game_camera_mode_local_parameter(void *, void *);

static void func_000EBDF8(void *cm, char *c, void *a2)
{
    int buf[4];
    char *m = c + 0x50;

    constructor_game_camera_param_update_data_manager(buf);
    func_000E5268(buf, cm, c, m, a2);
    doit_game_camera_param_manager(m, buf, cm, c, D_0017B720);
    get_game_camera_mode_local_parameter(m + 0x1334, c);
}
