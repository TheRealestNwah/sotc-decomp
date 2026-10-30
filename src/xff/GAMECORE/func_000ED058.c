extern int GAMEUTIL_is_inside_of_region_yaw(void *, void *, float, float, float);
extern int GAMEUTIL_is_inside_of_region_pitch(void *, void *, float, float, float);
extern float D_0017B720;

static void func_000ED058(char *w, char *cam, char *prm)
{
    float pitch;

    if (*(int *)(w + 0x88) != 0)
        return;
    pitch = *(float *)(prm + 0x14);
    if (GAMEUTIL_is_inside_of_region_yaw(0, 0, *(float *)(cam + 0x110), *(float *)(prm + 0x10), *(float *)(prm + 0x2C)) &&
        GAMEUTIL_is_inside_of_region_pitch(0, 0, *(float *)(cam + 0x114), pitch, *(float *)(prm + 0x58))) {
        *(float *)(w + 0x8C) += D_0017B720;
        if (*(float *)(prm + 0x20) <= *(float *)(w + 0x8C))
            *(int *)(w + 0x88) = 1;
    } else {
        *(float *)(w + 0x8C) = 0.0f;
    }
}
