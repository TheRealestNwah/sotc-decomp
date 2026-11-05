typedef struct {
    int n;
    int obj[7];
} JudgeData;

extern void ConstructorCollisionObjectJudgeCallbackData(JudgeData *);
extern void *get_cur_camera_target(void *);
extern int get_camera_move_collision_group(void *);
extern void *CAM_get_target_riding_obj(void *);
extern float get_camera_collision_data_base_filter_radius(float, float, float);
extern int CollisionObjectJudgeCallbackExceptPluralObj();
extern int CollisionPlaneJudgeCallbackCameraMove();
extern void GetCollisionDBCallBack(void *, int, void *, void *, int (*)(), int, int, int (*)(), float, JudgeData *);
extern int func_000D5CA8();
extern int ClipCollisionFinderWithVariableKeep4DCB(void *, void *, void *, void *, int (*)(), int, int, float *);
extern int ClipCollisionFinderWithVariableKeepCB(void *, void *, void *, void *, int (*)(), int, int, float *);

static inline void addObj(JudgeData *d, void *o)
{
    d->obj[d->n] = (int)o;
    d->n++;
}

int camera_collision_check_with_keep(void *out, char *cam, void *a2, void *a3, void *tgt, int keep4)
{
    float range[2];
    JudgeData data;
    JudgeData *d;
    char *db = cam + 0x1800;
    int group;
    void *ride;
    void *o;
    float r;
    float *rp = range;

    rp[0] = 0.1f;
    rp[1] = 0.4f;
    group = get_camera_move_collision_group(tgt);
    ride = CAM_get_target_riding_obj(cam + 0x23C);
    d = &data;
    ConstructorCollisionObjectJudgeCallbackData(d);
    if (ride != 0)
        addObj(d, ride);
    o = get_cur_camera_target(tgt);
    if (o != 0)
        addObj(d, o);
    r = get_camera_collision_data_base_filter_radius(0.1f, 0.1f, 0.4f);
    GetCollisionDBCallBack(db, group, a2, a3, CollisionObjectJudgeCallbackExceptPluralObj, 0, 0,
                           CollisionPlaneJudgeCallbackCameraMove, r, d);
    if (keep4 == 1)
        return ClipCollisionFinderWithVariableKeep4DCB(out, a2, a3, db, func_000D5CA8, 0, 0, rp);
    return ClipCollisionFinderWithVariableKeepCB(out, a2, a3, db, func_000D5CA8, 0, 0, rp);
}
