typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef struct {
    int n;
    int obj[7];
} JudgeData;

extern void ConstructorCollisionObjectJudgeCallbackData(JudgeData *);
extern void *get_cur_camera_target(void *);
extern int get_camera_move_collision_group(void *);
extern float get_camera_collision_data_base_filter_radius(float, float, float);
extern int CollisionObjectJudgeCallbackExceptPluralObj();
extern int CollisionPlaneJudgeCallbackCameraMove();
extern int func_000D5CA8();
extern void GetCollisionDBCallBack(void *, int, void *, void *, float, int (*)(), int, int, int (*)(), JudgeData *);
extern int ClipCollisionFinderWithVariableKeepCB(void *, void *, void *, void *, int (*)(), int, int, void *);
extern void CopyCollisionDynamics(void *, void *);

static inline void addObj(JudgeData *d, void *o)
{
    d->obj[d->n] = (int)o;
    d->n++;
}

int check_camera_position_float_by_collision(u_long128 *out, void *dyn, void *db, u_long128 *pos, void *player, void *except, int useTarget, float f0, float f1)
{
    u_long128 res[3];
    float fl[4];
    float r;
    JudgeData data;
    JudgeData *d;
    void *o;
    int group;

    group = get_camera_move_collision_group(player);
    fl[0] = f0;
    fl[1] = f1;
    d = &data;
    ConstructorCollisionObjectJudgeCallbackData(d);
    if (except != 0)
        addObj(d, except);
    if (useTarget == 1) {
        o = get_cur_camera_target(player);
        if (o != 0)
            addObj(d, o);
    }
    r = get_camera_collision_data_base_filter_radius(0.1f, f0, f1);
    GetCollisionDBCallBack(db, group, pos, pos, r, CollisionObjectJudgeCallbackExceptPluralObj, 0, 0,
                           CollisionPlaneJudgeCallbackCameraMove, d);
    if (ClipCollisionFinderWithVariableKeepCB(res, pos, pos, db, func_000D5CA8, 0, 0, fl) == 1) {
        *out = res[0];
        if (dyn != 0)
            CopyCollisionDynamics(dyn, res);
        return 1;
    }
    *out = *pos;
    return 0;
}
