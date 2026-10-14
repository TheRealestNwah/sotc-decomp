typedef int s128 __attribute__((mode(TI)));

typedef struct {
    s128 q;
} Vec4;

typedef struct {
    Vec4 pos;
    Vec4 target;
    Vec4 up;
    float roll;
    float fov_offset;
    float dist;
} ModeCommonCameraData;

extern Vec4 ZUnitVector;
extern Vec4 ZeroPoint;

void constructor_mode_common_camera_data(ModeCommonCameraData *d)
{
    d->pos = ZeroPoint;
    d->target = ZeroPoint;
    d->up = ZUnitVector;
    d->roll = d->fov_offset = 0.0f;
    d->dist = 4.5f;
}
