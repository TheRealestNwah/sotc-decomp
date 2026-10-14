struct StageCoordinateView {
    char pad00[0x28];
    int map_width;
    int map_height;
    char pad30[0x10];
    float scale_x;
    float scale_z;
    char pad48[8];
    float offset_x;
    float offset_z;
};

union StageCoordinateAlias {
    struct StageCoordinateView fields;
    float words[22];
};

extern union StageCoordinateAlias D_0017A340;

void getPosOnMap(const float *position, float *x, float *z)
{
    *x = (-position[0] * (float)D_0017A340.fields.map_width) / D_0017A340.fields.offset_x;
    *z = (-position[2] * (float)D_0017A340.fields.map_height) / D_0017A340.fields.offset_z;
}
