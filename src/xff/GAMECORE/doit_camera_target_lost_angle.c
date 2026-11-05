typedef int s128 __attribute__((mode(TI)));

extern int CAM_is_acting_view_cut_avoid_cntrl(void *);
extern int get_cur_attr_camera_default_angle(void *);
extern void CAM_act_warp_order_camera_warp_cntrl(void *);
extern int is_must_reach_normal_default_angle(char *, char *);
extern int GAMEUTIL_get_cur_status_status_manager(void *);
extern void *CAM_get_target_riding_obj(void *);
extern int CAM_act_ray_check_for_camera(void *, void *, void *, void *, int, void *);
extern void GAMEUTIL_set_data_by_dynamics_collision_info(void *, void *, int);
extern void func_000DB130(int *, void *, char *, void *, float);
extern void func_000DB2F8(void *, void *, void *, void *, void *, float);
extern int func_000DB080(int *, char *);
extern int func_000DB048(int *);

void doit_camera_target_lost_angle(int *st, char *cam, char *tgt, void *coll)
{
    char *m = cam + 0x520;
    s128 hit[3];
    s128 col[6];

    if (*(int *)(m + 0x44) == 0) {
        if (st[0] != 1 || *(int *)(tgt + 0x1360) != 1 || CAM_is_acting_view_cut_avoid_cntrl(cam + 0x16B0) == 0)
            st[0] = 0;
        return;
    }
    if (func_000DB080(st, cam) == 1) {
        if (get_cur_attr_camera_default_angle(cam + 0x730) == 2 && func_000DB048(st) == 1)
            CAM_act_warp_order_camera_warp_cntrl(cam + 0x1840);
        st[0] = 0;
        return;
    }
    if (is_must_reach_normal_default_angle(cam, tgt) == 0 && GAMEUTIL_get_cur_status_status_manager(cam + 0x554) == 0
        && *(int *)(m + 0x44) == 1) {
        func_000DB130(st, cam + 0x570, cam, coll, *(float *)(cam + 0x90));
        return;
    }
    if (st[0] != 0) {
        void *ride = CAM_get_target_riding_obj(cam + 0x23C);
        if (CAM_act_ray_check_for_camera(hit, m, (char *)st + 0x30, coll, 0, ride) == 0) {
            GAMEUTIL_set_data_by_dynamics_collision_info(col, hit, 0);
            func_000DB130(st, col, cam, coll, *(float *)(st + 8));
        } else {
            func_000DB2F8((char *)st + 0x10, st + 8, (char *)st + 0x24, (char *)st + 0x30, m, *(float *)(st + 8));
        }
    }
}
