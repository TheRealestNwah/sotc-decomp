typedef int u_long128 __attribute__((mode(TI)));

typedef struct {
    int n;
    int obj[7];
} JudgeData;

typedef struct {
    char pad0[0x40];
    float pos[4] __attribute__((aligned(16)));
} CollisionPoint;

extern void ConstructorCollisionObjectJudgeCallbackData(JudgeData *);
extern void *get_cur_camera_target(void *);
extern int get_player_collision_group_cameraman(void *);
extern int CollisionObjectJudgeCallbackExceptPluralObj();
extern int playerPlaneJudgeFuncCameraFilter();
extern int ClipCollisionDirectCallBack(void *, void *, void *, int, int (*)(), int, int, int (*)(), JudgeData *);
extern int GetWaterSurfacePositionY(float *, float *, int, float, float);
extern void ConstructorCollisionPoint(CollisionPoint *);
extern void CopyCollisionPoint(void *, CollisionPoint *);

static inline void addObj(JudgeData *d, void *o)
{
    d->obj[d->n] = (int)o;
    d->n++;
}

int player_collision_check_direct_water_surface_plus(void *out, float *start, float *end, void *player, void *except,
                                                     int useTarget)
{
    CollisionPoint hit;
    CollisionPoint water;
    JudgeData data;
    float waterY;
    JudgeData *d = &data;
    void *o;
    int hitRes;
    int waterRes;

    ConstructorCollisionObjectJudgeCallbackData(d);
    if (except != 0)
        addObj(d, except);
    if (useTarget == 1) {
        o = get_cur_camera_target(player);
        if (o != 0)
            addObj(d, o);
    }
    hitRes = ClipCollisionDirectCallBack(&hit, start, end, get_player_collision_group_cameraman(player),
                                         CollisionObjectJudgeCallbackExceptPluralObj, 0, 0,
                                         playerPlaneJudgeFuncCameraFilter, d);
    waterRes = GetWaterSurfacePositionY(&waterY, start, get_player_collision_group_cameraman(player), start[1], end[1]);
    if (waterRes == 1) {
        ConstructorCollisionPoint(&water);
        *(u_long128 *)water.pos = *(u_long128 *)start;
        water.pos[1] = waterY;
    }
    if (hitRes == 1) {
        if (waterRes == 1 && !(hit.pos[1] >= water.pos[1]))
            CopyCollisionPoint(out, &water);
        else
            CopyCollisionPoint(out, &hit);
    } else if (waterRes == 1) {
        CopyCollisionPoint(out, &water);
    }
    if (hitRes == 1 || waterRes == 1)
        return 1;
    return 0;
}
