typedef float sceVu0FMATRIX[4][4] __attribute__((aligned(16)));

typedef struct {
    char pad0[0x150];
    float filterBaseDist;
} CameraModeCommonData;

float get_mode_common_data_filter_base_dist_to_look_at(CameraModeCommonData **mode)
{
    sceVu0FMATRIX unused;
    return (*mode)->filterBaseDist;
}
