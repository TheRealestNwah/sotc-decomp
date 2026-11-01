extern char *GetLayoutClass(void *);
extern void func_000DCE28(char *, void *, char *, void *);
extern int GAMEUTIL_get_cur_status_status_manager(void *);
extern int camera_collision_check_direct(void *, void *, void *, void *, void *, int, void *, int);
extern void ConvertFromCollisionPointToDynamics(void *, void *);
extern void GAMEUTIL_reset_collision_info(char *);
extern void GAMEUTIL_set_data_by_dynamics_collision_info(void *, void *, int);

static inline int checkHit(void *dyn, void *ctx, void *from, void *to, char *sub)
{
    char hit[0x50] __attribute__((aligned(16)));
    int miss;

    miss = camera_collision_check_direct(hit, ctx, from, to, 0, 0, (void *)*(int *)(sub + 0x2C8), 1) == 0;

    if (!miss)
        ConvertFromCollisionPointToDynamics(dyn, hit);
    return miss;
}

void CAM_doit_objective_target_visibility(char *ctx, void *from, char *cam, void *arg, void *to)
{
    char dyn[0x30] __attribute__((aligned(16)));
    char *sub = cam + 0x23C;
    int miss;

    func_000DCE28(ctx, *(void **)(GetLayoutClass(*(void **)sub) + 0x134), cam, arg);
    *(int *)(ctx + 0x44) = GAMEUTIL_get_cur_status_status_manager(ctx + 0x34);
    miss = checkHit(dyn, ctx, from, to, sub);
    if (miss == 1) {
        GAMEUTIL_reset_collision_info(ctx + 0x50);
        *(int *)(ctx + 0x44) = 0;
    } else {
        GAMEUTIL_set_data_by_dynamics_collision_info(ctx + 0x50, dyn, 0);
        if (*(int *)(ctx + 0x44) == 0)
            *(int *)(ctx + 0x44) = 1;
    }
}
