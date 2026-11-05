typedef int s128 __attribute__((mode(TI)));

typedef struct {
    int a;
    int hit;
    int pad8;
    int ground;
    int boss;
    int pad14[3];
    s128 pos;
    int f30;
    float time;
} EtcCond;

extern s128 ZeroPoint;
extern int is_reset_or_lws_movie_or_cutout_game_camera(char *);
extern void *CAM_get_target_obj(void *);
extern char *GetLayoutClass(void *);
extern int is_hit_cam_opt_leave_collision_attribute(void *, int, int, void *);
extern char *GAMEUTIL_get_motion_kind(void *);
extern int GAMEUTIL_get_parent_collision_attribute(void *, void *);
extern int GAMEUTIL_is_horse_obj_contact_ground(int, void *);
extern int get_on_boss_camera_col_attr_camera_place_status(void *, void *);
extern void func_000D7CC8(EtcCond *);
extern void func_000D7CE8(EtcCond *, void *, void *, void *);

void doit_camera_etc_condition(EtcCond *st, char *cam, void *coll, float dt)
{
    char *tc;
    char *sub;
    void *tgt;
    char *lay;
    s128 pos;
    long long attr;
    long long battr;
    char *mk;
    int r;

    if (is_reset_or_lws_movie_or_cutout_game_camera(cam) == 1) {
        st->a = 0;
        st->ground = 0;
        st->boss = 0;
        func_000D7CC8(st);
        return;
    }
    tc = cam + 0x15AC;
    sub = cam + 0x1370;
    tgt = CAM_get_target_obj(tc);
    lay = GetLayoutClass(tgt);
    func_000D7CE8(st, tgt, tc, coll);
    if (is_hit_cam_opt_leave_collision_attribute(&pos, *(int *)(lay + 0x138), *(int *)(lay + 0x134), coll) == 1) {
        if (st->hit != 1) {
            st->hit = 1;
            st->pos = pos;
            st->f30 = 0;
        }
        st->time = 0;
    } else if (st->hit != 1) {
        st->hit = 0;
        st->pos = ZeroPoint;
        st->f30 = 0;
        st->time = 0;
    } else {
        mk = GAMEUTIL_get_motion_kind(tgt);
        attr = 0;
        if (mk != 0 && *(int *)(mk + 0x90) != 4 && GAMEUTIL_get_parent_collision_attribute(&attr, tgt) == 1) {
            st->time += dt;
            if (st->time >= 30.0f) {
                st->hit = 0;
                st->pos = ZeroPoint;
                st->f30 = 0;
                st->time = 0;
            }
        }
    }
    st->ground = GAMEUTIL_is_horse_obj_contact_ground(0, tgt);
    battr = 0;
    r = get_on_boss_camera_col_attr_camera_place_status(&battr, sub + 0x1270);
    if (r == 1 && (battr & 1) == 1)
        st->boss = r;
    else
        st->boss = 0;
}
