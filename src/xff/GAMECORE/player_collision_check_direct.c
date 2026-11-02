typedef struct {
    int n;
    int obj[7];
} JudgeData;

extern void ConstructorCollisionObjectJudgeCallbackData(JudgeData *);
extern void *get_cur_camera_target(void *);
extern int get_player_collision_group_cameraman(void *);
extern int CollisionObjectJudgeCallbackExceptPluralObj();
extern int playerPlaneJudgeFuncCameraFilter();
extern int ClipCollisionDirectCallBack(void *, void *, void *, int, int (*)(), int, int, int (*)(), JudgeData *);

static inline void addObj(JudgeData *d, void *o)
{
    d->obj[d->n] = (int)o;
    d->n++;
}

int player_collision_check_direct(void *a0, void *a1, void *a2, void *player, void *except, int useTarget)
{
    JudgeData data;
    JudgeData *d = &data;
    void *o;

    ConstructorCollisionObjectJudgeCallbackData(d);
    if (except != 0)
        addObj(d, except);
    if (useTarget == 1) {
        o = get_cur_camera_target(player);
        if (o != 0)
            addObj(d, o);
    }
    return ClipCollisionDirectCallBack(a0, a1, a2, get_player_collision_group_cameraman(player),
                                       CollisionObjectJudgeCallbackExceptPluralObj, 0, 0,
                                       playerPlaneJudgeFuncCameraFilter, d);
}
