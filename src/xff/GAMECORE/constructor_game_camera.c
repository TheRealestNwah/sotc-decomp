extern void constructor_camera_etc_condition(void *);
extern void constructor_game_camera_param_manager(void *);
extern void func_000E6140(void *, void *);
extern void func_000EB978(void *);
extern void func_000EB980(void *, int);
extern void func_000EB9D8(void *);
extern void func_000EBA50(void *);
extern void func_000EBAE8(void *);
extern void func_000EBB88(void *, int);
extern void func_000EBC40(void *);
extern void func_000EBC60(void *);
extern void func_000EBC78(void *);
extern void constructor_camera_pause_rise(void *);
extern void *get_interp_game_camera_param_game_camera_param_manager(void *);
extern void func_000EBC90(void *, void *);

void constructor_game_camera(char *g, void *arg)
{
    *(int *)(g + 0x0) = 0;
    *(int *)(g + 0x4) = 0;
    constructor_camera_etc_condition(g + 0x10);
    constructor_game_camera_param_manager(g + 0x50);
    *(int *)(g + 0x1360) = -1;
    *(int *)(g + 0x1364) = -1;
    func_000E6140(g + 0x1370, arg);
    func_000EB978(g + 0x2C40);
    func_000EB980(g + 0x2C44, 1);
    func_000EB9D8(g + 0x2D20);
    func_000EBA50(g + 0x2DE0);
    func_000EBAE8(g + 0x2ED0);
    func_000EBB88(g + 0x2FF0, 1);
    func_000EBC40(g + 0x3120);
    func_000EBC60(g + 0x3270);
    func_000EBC78(g + 0x34E0);
    constructor_camera_pause_rise(g + 0x3750);
    func_000EBC90(g, get_interp_game_camera_param_game_camera_param_manager(g + 0x50));
}
