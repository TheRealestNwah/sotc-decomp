typedef struct {
    char pad0[0x34];
    int atMin;
    int atMax;
    char state[0x40 - 0x3C];
    float value;
    char pad44[0x5C - 0x44];
    float yaw;
    char pad60[0x6C - 0x60];
    float p6C;
    float p70;
    char pad74[0x7C - 0x74];
    float p7C;
    float min;
    float max;
    char work[0x108 - 0x88];
    int useMin;
    int useMax;
    float baseYaw;
    float minYaw;
    float maxYaw;
} YawLimit;

extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern float GAMEUTIL_increase_yaw(int *, float, float);
extern int GAMEUTIL_is_between_yaw_and_yaw(float, float, float);
extern float func_0000DEC0(void *, void *, float, float, float, float, float, float, float);

static void func_0000C820(YawLimit *p, float dt)
{
    float yaw = p->yaw;
    float min = p->min;
    float max = p->max;
    int limited;
    float r;

    if (p->useMin == 1 || p->useMax == 1)
        limited = 1;
    else
        limited = 0;
    if (limited == 1) {
        int positive;

        if (GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(p->baseYaw, yaw) >= 0.0f)
            positive = 1;
        else
            positive = 0;
        if (positive == 1) {
            if (p->useMin == 1
                && !GAMEUTIL_is_between_yaw_and_yaw(GAMEUTIL_increase_yaw(0, yaw, p->min), p->baseYaw,
                                                    p->minYaw)) {
                min = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(yaw, p->minYaw);
                if (min < 0.0f)
                    min = 0.0f;
            }
        } else {
            if (p->useMax == 1
                && !GAMEUTIL_is_between_yaw_and_yaw(GAMEUTIL_increase_yaw(0, yaw, p->max), p->baseYaw,
                                                    p->maxYaw)) {
                max = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(yaw, p->maxYaw);
                if (0.0f < max)
                    max = 0.0f;
            }
        }
    }
    r = func_0000DEC0(p->state, p->work, p->p6C, p->p70, dt, p->value, p->p7C, min, max);
    p->atMax = 0;
    p->value = r;
    p->atMin = 0;
    if (min - 0.017453293f <= r)
        p->atMin = 1;
    else if (r <= max + 0.017453293f)
        p->atMax = 1;
}
