typedef struct {
    union {
        int state;
        float f;
    } u;
    char pad4[0x1C];
    float yaw;
    float pitch;
} LostTarget;

extern void func_000DB558(float *, float *, LostTarget *, void *);

int get_yaw_pitch_camera_target_lost_angle(float *yaw, float *pitch, LostTarget *t, void *d, float y,
                                           float p)
{
    float tmp[4];

    *yaw = y;
    *pitch = p;
    if (t->u.state == 1) {
        func_000DB558(yaw, tmp, t, d);
        return 1;
    }
    if (t->u.state == 2) {
        *yaw = t->yaw;
        if (t->pitch < *pitch)
            *pitch = t->pitch;
        return 1;
    }
    return 0;
}
