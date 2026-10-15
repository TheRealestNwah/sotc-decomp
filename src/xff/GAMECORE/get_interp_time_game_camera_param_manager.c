typedef struct {
    char pad0[0x20];
    float interpTime;
    char pad24[0x670 - 0x24];
    float defaultInterpTime;
} CameraParamManager;

float get_interp_time_game_camera_param_manager(CameraParamManager *manager)
{
    if (manager->interpTime < 0.0f) {
        return manager->defaultInterpTime;
    }
    return manager->interpTime;
}
