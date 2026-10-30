extern void GAMEUTIL_get_local_directionZ(float *, void *);
extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);

static float func_000706D0(void *obj)
{
    float dir[4];
    float yaw;
    float pitch;

    yaw = 0.0f;
    pitch = 0.0f;
    GAMEUTIL_get_local_directionZ(dir, obj);
    GAMEUTIL_get_yaw_pitch_by_direction(&yaw, &pitch, dir);
    return yaw;
}
