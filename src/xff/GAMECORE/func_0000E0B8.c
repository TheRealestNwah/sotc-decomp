extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern void GAMEUTIL_increase_yaw_limit_clip(int, int, float, float, float, float);
extern void GAMEUTIL_increase_yaw(int, float, float);

static void func_0000E0B8(char *o, float yaw)
{
    if (*(int *)(o + 0x10C) == 1) {
        int ok = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(*(float *)(o + 0x110), yaw) >= 0.0f;

        if (!ok) {
            GAMEUTIL_increase_yaw_limit_clip(0, 0, *(float *)(o + 0x118), -*(float *)(o + 0x84), *(float *)(o + 0x118), yaw);
            return;
        }
    }
    GAMEUTIL_increase_yaw(0, *(float *)(o + 0x118), -*(float *)(o + 0x84));
}
