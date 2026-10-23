typedef struct {
    char pad[0x6C];
    unsigned int pad0 : 6;
    unsigned int reset : 2;
} MotionKind;

typedef struct {
    char pad[0x178];
    unsigned long pad0 : 6;
    unsigned long reset : 2;
    char pad2[0x14F];
    void *motion;
} Cam;

extern MotionKind *GAMEUTIL_get_motion_kind(void *);

long CAM_motion_kind_get_interest_dir_reset_attr_target(Cam *cam)
{
    long attr = cam->reset;

    if (attr != 0) {
        return attr;
    }
    if (cam->motion != 0 && GAMEUTIL_get_motion_kind(cam->motion) != 0) {
        int r = GAMEUTIL_get_motion_kind(cam->motion)->reset;

        return r;
    }
    return 0;
}
