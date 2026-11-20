extern int func_000E1EC8(void *, void *);
extern int is_leave_camera_dist_to_look_at(void *);
extern int GAMEUTIL_is_nearly_equal_yaw(float, float, float);
extern int GAMEUTIL_is_nearly_equal_pitch(float, float, float);

static void func_000E1D58(char *a, char *b, float yaw, float pitch, float dt)
{
    int r = 0;

    if (*(int *)(a + 0xC) != 0) {
        if (func_000E1EC8(a, b) != 1) {
            if (is_leave_camera_dist_to_look_at(b) == 1 || *(int *)(a + 0xC) == 1 ||
                (GAMEUTIL_is_nearly_equal_yaw(*(float *)(b + 0x110), yaw, *(float *)(a + 0x14)) &&
                 (*(int *)(a + 0xC) != 3 ||
                  GAMEUTIL_is_nearly_equal_pitch(*(float *)(b + 0x114), pitch, *(float *)(a + 0x18)))))
                r = 1;
        }
    }
    if (r == 1)
        *(float *)(a + 0x10) += dt;
    else
        *(float *)(a + 0x10) = 0.0f;
}
