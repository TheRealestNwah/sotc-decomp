int GAMEUTIL_is_yaw_pitch_get_direction(float *dir)
{
    float y = dir[1];

    if (y < 0.0f) {
        if (-0.9999f <= y) {
            goto ok;
        } else {
            goto ng;
        }
    } else {
        if (y <= 0.9999f) {
            goto ok;
        } else {
            goto ng;
        }
    }

ok:
    return 1;
ng:
    return 0;
}
