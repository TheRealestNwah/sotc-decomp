#define NULL ((void *)0)
extern int CAM_get_ground_contact_obj(int *);
extern int GAMEUTIL_get_motion_kind(void *);

int CAM_get_motion_kind_follow_rot_axis_attr_target(int *camera) {
    int temp_v0_2;
    void *temp_v0;

    temp_v0_2 = CAM_get_ground_contact_obj(camera);
    if (temp_v0_2 != 0) {
        temp_v0 = (void *)GAMEUTIL_get_motion_kind((void *)temp_v0_2);
        if (temp_v0 != NULL) {
            return (*(int *)((char *)(temp_v0) + 0x6C)) & 0xF;
        }
    }
    return 1;
}
