#ifdef NONMATCHING
/* 122 diffs (140 words vs 138). Draft from the asm; control flow follows it exactly. list[20] pointers at sp+0 filled by func_000DBC18(&n, list), idx = func_000DBC88(n, list, a, b); with n >= 2 picks the neighbour (prev/next, wrapping) whose yaw range contains the reference yaw b+0xA94 (GAMEUTIL_is_between_yaw_and_yaw, falling back to the smaller get_difference_yaw_and_yaw); then func_000DBD88(list[idx], yaw, pitch, a, b) == 1 re-stores the cached yaw a+0x3D4 else caches list[idx][1..2] and sets a+0x3D0 = 1. Original spills out1 (a0) to sp+0x54 as the very first instruction (next to the count at 0x50) and keeps idx in s1 with the three list slots in s3/s4/s5; ours keeps idx in a1 and stores out1 only before the first jal. */
extern int GAMEUTIL_is_between_yaw_and_yaw(float, float, float);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float, float);
extern void func_000DBC18(int *, float **);
extern int func_000DBC88(int, float **, char *, char *);
extern int func_000DBD88(float *, float, float, char *, char *);

typedef struct {
    int n;
    float *out;
} Cnt;

int begin_and_update_get_yaw_pitch_camera_target_visible_angle_manager(float *out1, float *out2, float yaw, float pitch, char *a, char *b)
{
    float *list[20];
    Cnt c;
    float ref;
    int idx;
    int prev;
    int next;

    c.out = out1;
    c.n = 0;
    ref = *(float *)(b + 0xA94);
    *c.out = yaw;
    *out2 = pitch;
    func_000DBC18(&c.n, list);
    idx = func_000DBC88(c.n, list, a, b);
    if (idx < 0)
        return 0;
    if (c.n != 1) {
        float **pi, **pp, **pn;
        prev = idx - 1;
        next = idx + 1;
        if (!(next < c.n))
            next = 0;
        if (prev < 0)
            prev = c.n - 1;
        if (prev == next) {
            pi = &list[idx];
            pn = &list[next];
            if (GAMEUTIL_is_between_yaw_and_yaw(ref, (*pi)[1], (*pn)[1]) != 1)
                idx = next;
        } else {
            pi = &list[idx];
            pp = &list[prev];
            pn = &list[next];
            idx = next;
            if (GAMEUTIL_is_between_yaw_and_yaw(ref, (*pi)[1], (*pp)[1]) != 1) {
                idx = prev;
                if (GAMEUTIL_is_between_yaw_and_yaw(ref, (*pi)[1], (*pn)[1]) != 1) {
                    float d1 = GAMEUTIL_get_difference_yaw_and_yaw((*pp)[1], (*pi)[1]);
                    float d2 = GAMEUTIL_get_difference_yaw_and_yaw((*pn)[1], (*pi)[1]);
                    if (!(d1 < d2))
                        idx = next;
                }
            }
        }
    }
    if (func_000DBD88(list[idx], yaw, pitch, a, b) == 1) {
        *c.out = *(float *)(a + 0x3D4);
        return 1;
    }
    {
        float *p = list[idx];
        *(float *)(a + 0x3D4) = p[1];
        *(float *)(a + 0x3D8) = p[2];
        *c.out = p[1];
        *(int *)(a + 0x3D0) = 1;
    }
    return 1;
}
#endif
