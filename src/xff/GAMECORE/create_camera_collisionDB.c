typedef struct {
    int n;
    int obj[5];
} JudgeData;

extern void ConstructorCollisionObjectJudgeCallbackData(JudgeData *);
extern void *get_cur_camera_target(void);
extern float get_camera_collision_data_base_filter_radius(void *, float, float, float);
extern int CollisionObjectJudgeCallbackExceptPluralObj();
extern int CollisionPlaneJudgeCallbackCameraMove();
extern void *GetCollisionDBCallBack(void *, void *, void *, void *, void *, int, int, void *, float, JudgeData *);

static inline void addObj(JudgeData *d, void *o)
{
    d->obj[d->n] = (int)o;
    d->n++;
}

void *create_camera_collisionDB(void *db, void *pos, void *a2, void *except, int useTarget, void *a5, void *a6, float x, float y, float z)
{
    JudgeData data;
    JudgeData *d = &data;

    void *o;

    ConstructorCollisionObjectJudgeCallbackData(d);

    if (except != 0)
        addObj(d, except);
    o = pos;
    if (useTarget == 1) {
        o = get_cur_camera_target();
        if (o != 0)
            addObj(d, o);
    }
    return GetCollisionDBCallBack(db, a2, a5, a6, CollisionObjectJudgeCallbackExceptPluralObj, 0, 0,
                                  CollisionPlaneJudgeCallbackCameraMove,
                                  get_camera_collision_data_base_filter_radius(o, x, y, z), d);
}
