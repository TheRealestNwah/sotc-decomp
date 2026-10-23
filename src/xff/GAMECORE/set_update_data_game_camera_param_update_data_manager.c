typedef struct {
    float value;
    int mode;
    char param[0x654];
} CameraParamUpdateData;

typedef struct {
    int pad;
    /* The char member lets stores through the data pointer alias it, so it is
       reloaded after every store, as in the original. */
    union {
        CameraParamUpdateData *data;
        char alias;
    } data;
} CameraParamUpdateDataManager;

static int get_best_mode_manager(int, int, int);
static void func_000EDCA8(void *, int);

void set_update_data_game_camera_param_update_data_manager(CameraParamUpdateDataManager *mgr, int index, int mode, int a, int b, float value)
{
    mgr->data.data[index].value = value;
    mgr->data.data[index].mode = mode;
    func_000EDCA8(mgr->data.data[index].param, get_best_mode_manager(mode, a, b));
}
