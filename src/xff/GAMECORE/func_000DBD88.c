typedef struct {
    char pad000[0x3D0];
    int mode;
    float yaw;
    char pad3D8[0x10];
    float range;
} CamDBD88;

typedef struct {
    char pad00[0x30];
    float yaw;
    float pitch;
} AngDBD88;

extern int CAM_is_visible_now_target_visibility(void *);
extern int GAMEUTIL_is_nearly_equal_yaw(float a, float b, float tol);
extern int GAMEUTIL_is_nearly_equal_pitch(float a, float b, float tol);
extern float GAMEUTIL_get_difference_yaw_and_yaw(float a, float b);

static int func_000DBD88(float *pos, CamDBD88 *cam, char *tgt, float unused, float pitch)
{
    AngDBD88 *ang;
    int r;

    if (cam->mode == 1) {
        ang = (AngDBD88 *)(tgt + 0x60);
        if (!CAM_is_visible_now_target_visibility(tgt + 0x520)) {
            r = GAMEUTIL_is_nearly_equal_yaw(cam->yaw, ang->yaw, 0.034906585f);
            if (r == 1 && GAMEUTIL_is_nearly_equal_pitch(pitch, ang->pitch, 0.034906585f) == r) {
                return 0;
            }
        }
        if (GAMEUTIL_get_difference_yaw_and_yaw(pos[1], cam->yaw) <= cam->range * 1.2f) {
            return 1;
        }
    }
    return 0;
}
