struct StageCoordinateView {
    char pad00[0x40];
    float scale_x;
    float scale_z;
    char pad48[8];
    float offset_x;
    float offset_z;
};

extern struct StageCoordinateView D_0017A340;

void getStageChipIDFloat(const float *position, float *x, float *z)
{
    *x = (-position[0] - D_0017A340.offset_x) / D_0017A340.scale_x;
    *z = (-position[2] - D_0017A340.offset_z) / D_0017A340.scale_z;
}
