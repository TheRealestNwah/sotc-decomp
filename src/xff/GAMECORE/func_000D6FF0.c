extern void *CAM_get_target_obj(void *);
extern int get_place_status_camera_place_status(void *);
extern void *get_manage_obj_camera_place_status(void *);
extern void *GAMEUTIL_get_parent_object(void *);
extern void *GAMEUTIL_get_boss_obj(void);

static void *func_000D6FF0(int kind, char *c)
{
    void *r = 0;
    char *ps = c + 0x1270;

    switch (kind) {
    case 100:
        break;
    case 101:
        r = CAM_get_target_obj(c + 0x23C);
        break;
    case 102:
        if (get_place_status_camera_place_status(ps) == 2) {
            r = get_manage_obj_camera_place_status(ps);
        } else {
            r = GAMEUTIL_get_parent_object(CAM_get_target_obj(c + 0x23C));
        }
        break;
    case 103:
        r = get_manage_obj_camera_place_status(ps);
        break;
    case 104:
        r = GAMEUTIL_get_boss_obj();
        break;
    case 105:
        break;
    }
    return r;
}
