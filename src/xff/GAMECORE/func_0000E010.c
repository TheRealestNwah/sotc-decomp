typedef struct {
    char pad0[0x80];
    float speed;
    char pad84[0x108 - 0x84];
    int mode;
    char pad10C[0x110 - 0x10C];
    float target;
    float yaw;
} Turner;

extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern void GAMEUTIL_increase_yaw_limit_clip(void *, int, float, float, float, float);
extern void GAMEUTIL_increase_yaw(void *, float, float);

static inline int isCcw(float d)
{
    if (0.0f <= d)
        return 1;
    return 0;
}

static void func_0000E010(Turner *t, float limit)
{
    if (t->mode == 1 && isCcw(GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(t->target, limit)) == 1) {
        GAMEUTIL_increase_yaw_limit_clip(0, 0, t->yaw, -t->speed, t->yaw, limit);
        return;
    }
    GAMEUTIL_increase_yaw(0, t->yaw, -t->speed);
}
