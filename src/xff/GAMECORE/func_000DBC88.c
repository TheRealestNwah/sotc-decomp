extern float RO_00181048;
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern int GAMEUTIL_is_between_yaw_and_yaw(float, float, float);

static int func_000DBC88(int n, char **items, char *c, char *d)
{
    float best = RO_00181048;
    int idx = -1;
    float yaw = *(float *)(d + 0xA94);
    int i;

    for (i = 0; i < n; i++) {
        float diff = GAMEUTIL_get_difference_yaw_and_yaw(*(float *)(items[i] + 4), yaw);

        if (*(int *)(c + 0x3D0) == 1
            && GAMEUTIL_is_between_yaw_and_yaw(yaw, *(float *)(items[i] + 4), *(float *)(c + 0x3D4)) == 1)
            diff += 0.0872664626f;
        if (diff < best) {
            best = diff;
            idx = i;
        }
    }
    return idx;
}
