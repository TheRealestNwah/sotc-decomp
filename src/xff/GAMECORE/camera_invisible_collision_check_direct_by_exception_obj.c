typedef struct {
    int n;
    int obj[7];
} JudgeData;

extern void ConstructorCollisionObjectJudgeCallbackData(JudgeData *);
extern void *get_cur_camera_target(void *);
extern int get_camera_move_collision_group(void *);
extern int func_000D5C28();
extern int ClipCollisionDirectCallBack(void *, void *, void *, int, int (*)(), int, int, int (*)(), JudgeData *);

static inline void addObj(JudgeData *d, void *o)
{
    d->obj[d->n] = (int)o;
    d->n++;
}

int camera_invisible_collision_check_direct_by_exception_obj(void *a0, void *a1, void *a2, void *player, void *except, int useTarget)
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
    return ClipCollisionDirectCallBack(a0, a1, a2, get_camera_move_collision_group(player),
                                       func_000D5C28, 0, 0, 0, d);
}
