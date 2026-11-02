extern void GAMEUTIL_get_local_directionZ(float *, int);
extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern int GAMEUTIL_is_between_yaw_and_yaw_extend_abs(float, float, float, float);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

int is_enable_reach_src_yaw_nico_sight_on(float *out, char *w, float yaw)
{
    float dir[4];
    float y;
    float p;
    float center;
    float left;
    float right;
    float yv;

    if (out != 0)
        *out = 0;
    if (*(int *)(w + 0x2B8) == 1) {
        y = 0.0f;
        p = 0.0f;
        GAMEUTIL_get_local_directionZ(dir, *(int *)(w + 4));
        GAMEUTIL_get_yaw_pitch_by_direction(&y, &p, dir);
        yv = y;
        center = GAMEUTIL_increase_yaw(0, yv, *(float *)(w + 0x2C4));
        if (*(int *)(w + 0x2BC) == 1)
            left = GAMEUTIL_increase_yaw(0, yv, *(float *)(w + 0x2C8));
        else
            left = GAMEUTIL_increase_yaw(0, yv, *(float *)(w + 0x2D0));
        if (*(int *)(w + 0x2C0) == 1)
            right = GAMEUTIL_increase_yaw(0, yv, *(float *)(w + 0x2CC));
        else
            right = GAMEUTIL_increase_yaw(0, yv, *(float *)(w + 0x2D4));
        if (GAMEUTIL_is_between_yaw_and_yaw_extend_abs(yaw, center, left, right))
            return 1;
        if (out != 0) {
            float d1 = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(left, yaw);
            float d2 = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(right, yaw);

            if (ABS(d1) < ABS(d2))
                *out = d1;
            else
                *out = d2;
        }
        return 0;
    }
    return 1;
}
