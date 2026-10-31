extern void *CAM_get_target_obj(void);
extern void *GAMEUTIL_get_riding_horse_object(void *);

static float func_000DAD60(void *cam, int mode)
{
    float r = 1.0f;

    if (GAMEUTIL_get_riding_horse_object(CAM_get_target_obj()))
        r = 2.0f;
    if (mode == 1)
        r += 0.5f;
    return r;
}
