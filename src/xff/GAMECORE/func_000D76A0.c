typedef struct {
    char pad0[4];
    int a;
    int b;
} CamState;

extern int CAM_is_return_cam_posi_target_visibility(char *);
extern int CAM_is_visible_now_target_visibility(char *);
extern int is_safety_camera_default_angle(char *);
extern float GAMEUTIL_get_status_continue_time_status_manager(char *);
extern void *CAM_get_target_riding_obj(char *);
extern int camera_invisible_collision_check_direct_by_exception_obj(char *, char *, char *, void *, void *, int);

static int func_000D76A0(int *mode, char *cam, char *g, void *arg)
{
    char work[0x50];
    char *vis = cam + 0x520;
    int r;

    if (*mode != 2 && (*(int *)(g + 0x1364) == 1 || *(int *)(g + 0x1360) == 1)
        && (*(CamState **)(g + 0x2C44))->a != 1)
        goto check;
    if (CAM_is_return_cam_posi_target_visibility(vis) == 1)
        return 1;
    if (CAM_is_visible_now_target_visibility(vis))
        goto check;
    if (!is_safety_camera_default_angle(cam + 0x730))
        return 2;
    if (GAMEUTIL_get_status_continue_time_status_manager(vis + 0x34) >= 3.0f)
        return 2;
check:
    if (*(int *)(g + 0x1360) == 1 && (*(CamState **)(g + 0x2C44))->b == 1) {
        r = CAM_is_visible_now_target_visibility(vis);
        if (r == 1) {
            if (camera_invisible_collision_check_direct_by_exception_obj(work, vis, cam + 0x60, arg,
                                                                     CAM_get_target_riding_obj(cam + 0x23C), 1) == r)
                return 2;
        }
    }
    return 0;
}
