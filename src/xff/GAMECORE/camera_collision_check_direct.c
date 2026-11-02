typedef struct {
    int n;
    int obj[7];
} JudgeData;

extern void ConstructorCollisionObjectJudgeCallbackData(JudgeData *);
extern void *get_cur_camera_target(void *);
extern int get_camera_move_collision_group(void *);
extern int get_camera_visible_collision_group(void *);
extern int CollisionObjectJudgeCallbackExceptPluralObj();
extern int CollisionObjectJudgeCallbackExceptDescendPluralObj();
extern int CollisionPlaneJudgeCallbackCameraMove();
extern int CollisionPlaneJudgeCallbackCameraVisibility();
extern int ClipCollisionDirectCallBack(void *, void *, void *, int, int (*)(), int, int, int (*)(), JudgeData *);

static inline void addObj(JudgeData *d, void *o)
{
    d->obj[d->n] = (int)o;
    d->n++;
}

int camera_collision_check_direct(void *a0, void *a1, void *a2, void *cam, int move, int descend, void *except,
                                  int useTarget)
{
    JudgeData data;
    JudgeData *d = &data;
    void *o;
    int (*objcb)();
    int (*planecb)();
    int group;

    ConstructorCollisionObjectJudgeCallbackData(d);
    if (except != 0)
        addObj(d, except);
    if (useTarget == 1) {
        o = get_cur_camera_target(cam);
        if (o != 0)
            addObj(d, o);
    }
    if (descend == 1)
        objcb = CollisionObjectJudgeCallbackExceptDescendPluralObj;
    else
        objcb = CollisionObjectJudgeCallbackExceptPluralObj;
    if (move == 1) {
        group = get_camera_move_collision_group(cam);
        planecb = CollisionPlaneJudgeCallbackCameraMove;
    } else {
        group = get_camera_visible_collision_group(cam);
        planecb = CollisionPlaneJudgeCallbackCameraVisibility;
    }
    return ClipCollisionDirectCallBack(a0, a1, a2, group, objcb, 0, 0, planecb, d);
}
