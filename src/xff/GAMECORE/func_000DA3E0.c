extern float GAMEUTIL_get_yaw_by_direction(void *arg0);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float a, float b);
extern void GAMEUTIL_get_direction_by_yaw(void *out, float yaw);
extern float RO_00181044;
extern void func_000D9B30(char *, void *, void *, void *, float);

static void func_000DA3E0(char *p, void *a, void *dir, void *c, float f)
{
    float dirv[4] __attribute__((aligned(16)));
    float yaw = GAMEUTIL_get_yaw_by_direction(dir);
    float cur = *(float *)(p + 0x148);

    if (cur == RO_00181044 || GAMEUTIL_get_difference_yaw_and_yaw(cur, yaw) >= 0.0523598753f)
        *(float *)(p + 0x148) = yaw;
    GAMEUTIL_get_direction_by_yaw(dirv, *(float *)(p + 0x148));
    *(int *)(p + 0x2C) = 0;
    *(int *)(p + 0x34) = 0;
    func_000D9B30(p, a, dir, c, f);
    if (*(int *)(p + 0x14C) == 1) {
        *(float *)(p + 0x2C) = *(float *)(p + 0x174);
        *(float *)(p + 0x34) = *(float *)(p + 0x170);
    }
}
