/* Steps the camera point 0.01 units from `from` toward `to` and clips it
 * against the collision DB, skipping `except` and optionally the camera target. */

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

static inline void addObj(JudgeData *d, void *o)
{
    d->obj[d->n] = (int)o;
    d->n++;
}

int get_camera_position_float_by_hit_collision(u_long128 *out, u_long128 *to, u_long128 *from, void *db, void *player, void *except, int useTarget, float f0, float f1)
{
    u_long128 pt[1];
    u_long128 seg[1];
    u_long128 res[3];
    float fl[2];
    float len;
    float r;
    JudgeData data;
    JudgeData *d;
    void *o;
    int group;
    u_long128 *p;

    group = get_camera_move_collision_group(player);
    fl[0] = f0;
    fl[1] = f1;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(to), "r"(from), "r"(seg) : "memory");
    __asm__ __volatile__("lqc2 vf7, 0x0(%1)\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(len) : "r"(seg) : "$2", "memory");
    r = 0.01f / len;
    __asm__ __volatile__("mfc1 $2, %1\n"
                         "lqc2 vf5, 0x0(%0)\n"
                         "qmtc2.ni $2, vf6\n"
                         "vmulx.xyz vf5, vf5, vf6x\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(seg), "f"(r) : "$2", "memory");
    p = pt;
    __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                         "lqc2 vf6, 0x0(%1)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%2)\n"
                         : : "r"(from), "r"(seg), "r"(p) : "memory");
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
    GetCollisionDBCallBack(db, group, p, p, r, CollisionObjectJudgeCallbackExceptPluralObj, 0, 0,
                           CollisionPlaneJudgeCallbackCameraMove, d);
    if (ClipCollisionFinderWithVariableKeepCB(res, pt, pt, db, func_000D5CA8, 0, 0, fl) == 1) {
        *out = res[0];
        return 1;
    }
    *out = pt[0];
    return 0;
}
