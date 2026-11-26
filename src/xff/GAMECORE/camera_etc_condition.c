/* Camera etc condition: tracks the player's surroundings (leave-collision
 * hits, horse ground contact, boss riding, water) for the game camera, and
 * answers the camera's condition queries from them. */

typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
} VecQ;

typedef struct {
    int inWater;
    int hit;
    int pad8;
    int ground;
    int boss;
    int pad14[3];
    s128 pos;
    int f30;
    float time;
} EtcCond;

typedef struct {
    int a;
    int b;
    int c;
    int d;
    int e;
} CameraEtcFlags;

typedef struct {
    char pad[0x50];
} __attribute__((aligned(16))) WaterHit;

extern s128 ZeroPoint;
extern int opflowAdvertiseDemoStat;

extern int is_reset_or_lws_movie_or_cutout_game_camera(char *);
extern void *CAM_get_target_obj(void *);
extern void *CAM_get_target_riding_obj(void *);
extern char *GetLayoutClass(void *);
extern int is_hit_cam_opt_leave_collision_attribute(void *, int, int, void *);
extern char *GAMEUTIL_get_motion_kind(void *);
extern int GAMEUTIL_get_parent_collision_attribute(void *, void *);
extern int GAMEUTIL_is_horse_obj_contact_ground(int *, void *);
extern int GAMEUTIL_is_boss_booting(void);
extern int get_on_boss_camera_col_attr_camera_place_status(void *, void *);
extern int player_collision_check_direct_water_surface_plus(void *, void *, void *, void *, void *, int);
extern char *get_game_camera(void *);

static void func_000D7CA0(EtcCond *st);
static void func_000D7CC8(EtcCond *st);
static void func_000D7CE8(EtcCond *st, void *target, void *cam, void *player);

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
        st->inWater = 0;
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

void constructor_camera_etc_condition(EtcCond *st)
{
    func_000D7CA0(st);
    st->pad8 = 0;
}

int is_pass_camera_etc_condition(unsigned int cond, CameraEtcFlags *f)
{
    int r = 0;

    switch (cond) {
    case 0:
        r = 0;
        break;
    case 1:
        r = 1;
        break;
    case 2:
        r = f->a;
        break;
    case 3:
        r = f->b;
        break;
    case 4:
        r = GAMEUTIL_is_boss_booting();
        break;
    case 5:
        r = f->c;
        break;
    case 6:
        r = f->d;
        break;
    case 7:
        r = f->d == 0;
        break;
    case 8:
        if (opflowAdvertiseDemoStat == 1)
            r = 1;
        break;
    case 9:
        if (opflowAdvertiseDemoStat == 2)
            r = 1;
        break;
    case 10:
        r = f->e;
        break;
    case 11:
        r = f->e == 0;
        break;
    }
    return r;
}

void set_post_boss_dead_playable_flag_camera_etc_condition(void *object, int flag)
{
    *(int *)(get_game_camera(object) + 0x18) = flag;
}

static void func_000D7CA0(EtcCond *st)
{
    st->inWater = 0;
    st->ground = 0;
    st->boss = 0;
    func_000D7CC8(st);
}

static void func_000D7CC8(EtcCond *st)
{
    st->hit = 0;
    st->pos = ZeroPoint;
    st->f30 = 0;
    st->time = 0;
}

/* Checks whether the camera's target stands in water deep enough to matter. */
static void func_000D7CE8(EtcCond *st, void *target, void *cam, void *player)
{
    WaterHit hit;
    VecQ start;
    VecQ end;
    int horse;

    horse = GAMEUTIL_is_horse_obj_contact_ground(0, target);
    end.q = start.q = **(s128 **)(GetLayoutClass(target) + 0x134);
    if (st->inWater == 1) {
        if (horse == 1) {
            end.f[1] -= 2.0f;
        } else {
            end.f[1] -= 1.0f;
        }
    } else {
        if (horse == 1) {
            end.f[1] -= 3.5f;
        } else {
            end.f[1] -= 2.5f;
        }
    }
    st->inWater = player_collision_check_direct_water_surface_plus(&hit, &start, &end, player, CAM_get_target_riding_obj(cam), 1) != 1;
}
