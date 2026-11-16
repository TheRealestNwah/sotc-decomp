typedef struct CamSeg {
    int pad0;
    int place;
    int sub;
    int padC;
    int layout;
    int pad14;
    long f18;
    char pad20[4];
    int type;
    int pad28;
    int kind;
    int pad30;
    unsigned int cond;
    char pad38[0x10];
} CamSeg;

typedef struct CamCond {
    int place;
    int sub;
    int layout;
    int count;
    void *obj[3];
    int type[3];
    int kind[3];
    char *etc;
    int t2;
} CamCond;

extern CamSeg *get_mode_condition_segment_camera_place_status(int *, int, char *);
extern void *CAM_get_target_obj(char *);
extern char *GetCharacterClass(void *);
extern int func_000EC3E8(void *);
extern int get_hit_camera_region_camera_place_status(void *);
extern int is_parent_obj_boss_camera_region(int);
extern void *get_manage_obj_camera_place_status(void *);
extern void func_000EC2D0(int *, int *, void *, char *);
extern int is_pass_camera_etc_condition(unsigned int, void *);
extern void reset_game_camera_param_update_data_manager(void *, int);
extern void set_update_data_game_camera_param_update_data_manager(void *, int, CamSeg *, void *, char *, float);

static inline void camCondInit(CamCond *c, int place, int sub, char *etc, int t2, void *target, void *lobj)
{
    char *cls = GetCharacterClass(target);
    int cnt = 0;

    c->place = place;
    c->sub = sub;
    c->layout = func_000EC3E8(lobj);
    if (cls != 0) {
        c->obj[0] = *(void **)(cls + 0x950);
        cnt = 1;
        func_000EC2D0(&c->type[0], &c->kind[0], *(void **)(cls + 0x950), etc);
        if (*(void **)(cls + 0x950) != target) {
            c->obj[1] = target;
            func_000EC2D0(&c->type[1], &c->kind[1], target, etc);
            cnt = 2;
        }
    }
    c->count = cnt;
    c->etc = etc;
    c->t2 = t2;
}

static inline int camSegMatch(CamSeg *seg, CamCond *c)
{
    int j;

    if (seg->place == c->place
        && (seg->sub == c->sub || seg->sub == 1000000)
        && (seg->layout == c->layout || seg->layout == 1000000)) {
        for (j = 0; j < c->count; j++) {
            if (seg->type == c->type[j] && (seg->kind == c->kind[j] || seg->kind == 1000000)) {
                if (is_pass_camera_etc_condition(seg->cond, c->etc + 0x10) == 1)
                    return 1;
            }
        }
    }
    return 0;
}

static int func_000E54E0(void *mgr, char *cam, void *data, int place, int sub, char *etc, int t2)
{
    CamCond c;
    int n;
    CamSeg *seg;
    int i;

    n = 0;
    seg = get_mode_condition_segment_camera_place_status(&n, 0, cam + 0x1270);
    camCondInit(&c, place, sub, etc, t2, CAM_get_target_obj(cam + 0x23C), 0);
    for (i = 0; i < n; i++) {
        if (camSegMatch(&seg[i], &c) == 1) {
            reset_game_camera_param_update_data_manager(mgr, 1);
            set_update_data_game_camera_param_update_data_manager(mgr, 0, &seg[i], data, cam, 1.0f);
            return 1;
        }
    }
    return 0;
}

static int func_000E5738(void *mgr, char *cam, void *data, int place, int sub, char *etc, int t2)
{
    CamCond c;
    int n;
    int boss;
    void *lobj;
    CamSeg *seg;
    int i;

    n = 0;
    boss = is_parent_obj_boss_camera_region(get_hit_camera_region_camera_place_status(cam + 0x1270));
    lobj = get_manage_obj_camera_place_status(cam + 0x1270);
    seg = get_mode_condition_segment_camera_place_status(&n, 1, cam + 0x1270);
    camCondInit(&c, place, sub, etc, t2, CAM_get_target_obj(cam + 0x23C), lobj);
    for (i = 0; i < n; i++) {
        if (boss != 0 && seg[i].f18 != 0x1F0000 && seg[i].f18 != 0x1F8000)
            continue;
        if (camSegMatch(&seg[i], &c) == 1) {
            reset_game_camera_param_update_data_manager(mgr, 1);
            set_update_data_game_camera_param_update_data_manager(mgr, 0, &seg[i], data, cam, 1.0f);
            return 1;
        }
    }
    return func_000E54E0(mgr, cam, data, place, sub, etc, t2);
}

typedef struct CamPlaceEnt {
    long mask;
    float w;
    int padC;
} CamPlaceEnt;

extern int is_already_set_game_camera_param_update_data_manager(void *, int);

static int func_000E5A10(void *mgr, char *cam, void *data, int place, int sub, char *etc, int t2)
{
    CamCond c;
    int n;
    int ret;
    void *lobj;
    CamSeg *seg;
    int k;
    int m;
    int last;
    int i;
    char *ps = cam + 0x1270;

    lobj = get_manage_obj_camera_place_status(ps);
    ret = 0;
    if (lobj != 0) {
        n = 0;
        seg = get_mode_condition_segment_camera_place_status(&n, 2, ps);
        camCondInit(&c, place, sub, etc, t2, CAM_get_target_obj(cam + 0x23C), lobj);
        m = *(int *)(ps + 0x1C);
        reset_game_camera_param_update_data_manager(mgr, m);
        for (k = 0; k < m; k++) {
            CamPlaceEnt *e = &((CamPlaceEnt *)(ps + 0x20))[k];
            long mask = e->mask & 0x1F8000;
            last = m - 1;
            for (i = 0; i < n; i++) {
                if (seg[i].f18 != mask && seg[i].f18 != 0x1F8000)
                    continue;
                if (camSegMatch(&seg[i], &c) == 1) {
                    set_update_data_game_camera_param_update_data_manager(mgr, k, &seg[i], data, cam, e->w);
                    break;
                }
            }
            if (is_already_set_game_camera_param_update_data_manager(mgr, k) == 0)
                break;
            if (k == last)
                ret = 1;
        }
    }
    if (ret == 1)
        return 1;
    return func_000E54E0(mgr, cam, data, place, sub, etc, t2);
}
