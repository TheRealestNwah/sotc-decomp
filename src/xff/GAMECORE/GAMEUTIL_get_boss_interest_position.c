typedef int s128 __attribute__((mode(TI)));
typedef struct {
    float x, y, z, w;
} Vec4f;
typedef struct {
    char p0[0x2B0];
    char playerGroup[8];
    char bossGroup[4];
} GcGlobalVar;
typedef struct {
    char p0[0x54];
    int node;
    char p58[0x18];
    s128 ofs;
    char p80[0x10];
} InterestData;
extern GcGlobalVar gcGlobalVar;
extern s128 ZeroPoint;
extern int D_00179AE8;
extern s128 D_00179AF0;
extern void *isysGroupForFirst(void *, int);
extern void isysGroupForExit(void *, int);
extern void *isysGroupForNext(void *, int);
extern int nico_playerIsActingSightOn(void *);
extern int func_0000A898(s128 *);
extern int bossStatBootChk(void);
extern int get_interest_type_camera_lws_animation(void);
extern int get_interest_type_camera_lws_animation_data(InterestData *, int, void *);
extern int GAMEUTIL_get_node_quaternion_posi_by_id(s128 *, s128 *, void *, int);
extern void GetOffsetPositionQuaternion(s128 *, s128 *, s128 *, s128 *);
extern char *GetCharacterClass(void *);
extern int GetSkeletonFocusNode(void *);
extern int GAMEUTIL_get_node_posi_by_id(s128 *, void *, int);
extern void *bossStatGetActiveBoss(void);
extern void bossStatGetBossCloudPos(s128 *, void *);

int GAMEUTIL_get_boss_interest_position(s128 *out, int mode)
{
    InterestData data;
    s128 q;
    s128 p;
    void **it;
    void *boss = 0;
    void *player;
    void *obj;
    s128 *pq;
    s128 *pp;
    void *b;
    int ok;
    int type;

    obj = 0;
    for (it = isysGroupForFirst(gcGlobalVar.bossGroup, 0); it != 0; it = isysGroupForNext(it, 0)) {
        obj = *it;
        boss = obj;
        break;
    }
    if (obj != 0)
        isysGroupForExit(obj, 0);
    obj = 0;
    player = 0;
    for (it = isysGroupForFirst(gcGlobalVar.playerGroup, 0); it != 0; it = isysGroupForNext(it, 0)) {
        obj = *it;
        player = obj;
        break;
    }
    if (obj != 0)
        isysGroupForExit(obj, 0);
    ok = nico_playerIsActingSightOn(player);
    if (ok == 1 && func_0000A898(out) == ok)
        return ok;
    if (D_00179AE8 == 0) {
        *out = D_00179AF0;
        return 1;
    }
    if (boss != 0) {
        ok = bossStatBootChk() > 0;
        if (ok == 1) {
            type = get_interest_type_camera_lws_animation();
            if (type != 0) {
                if (get_interest_type_camera_lws_animation_data(&data, type, boss) == ok &&
                    GAMEUTIL_get_node_quaternion_posi_by_id(pq = &q, pp = &p, boss, data.node) == ok) {
                    GetOffsetPositionQuaternion(out, pp, &data.ofs, pq);
                    return 1;
                }
            } else {
                if (GAMEUTIL_get_node_posi_by_id(out, boss,
                        GetSkeletonFocusNode(*(char **)(GetCharacterClass(boss) + 0x750) + 0x10)) == ok)
                    return ok;
            }
        }
    }
    if (mode == 1) {
        b = bossStatGetActiveBoss();
        if (b != 0) {
            bossStatGetBossCloudPos(out, b);
            ((Vec4f *)out)->y += 140.0f;
            return 1;
        }
    }
    *out = ZeroPoint;
    return 0;
}
