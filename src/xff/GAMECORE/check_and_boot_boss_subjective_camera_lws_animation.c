extern void *GAMEUTIL_get_player_obj(void);
extern void *GAMEUTIL_get_boss_obj(void);
extern int get_boss_subjective_camera_lws_animation_param(void);
extern int get_main_type_camera_lws_animation(void);
extern char *GetLayoutClass(void *);
extern int get_camera_lws_animation_param(int);
extern int bossStatGetActiveBoss(void);
extern void end_camera_lws_animation_by_paramID(int);
extern void boot_camera_lws_animation_by_script(int);
extern void sePlaySystemSound(int);
extern int BossStatus_SNAKE_C;
extern int BossStatus_NARGA;
extern int SeList_beep_test;
extern struct { char pad[0x330]; int btnA; int pad334; int btnB; } gcGlobalVar;
extern struct { int on; int pad4; int trg; } padManagerData;

static inline float distXZsq(void *a, void *b)
{
    float d;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xz vf7, vf7, vf7\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni $2, vf7\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static inline int bossCamOk(void *boss)
{
    int b = bossStatGetActiveBoss();
    int r;
    float y;
    if (b == BossStatus_SNAKE_C) {
        if (*(float *)(*(char **)(GetLayoutClass(boss) + 0x134) + 4) < -37.5f)
            return 0;
    } else if (b == BossStatus_NARGA) {
        if (*(float *)(*(char **)(GetLayoutClass(boss) + 0x134) + 4) < -13.5f)
            return 0;
    }
    return 1;
}

void check_and_boot_boss_subjective_camera_lws_animation(float nearDist, float farDist)
{
    void *player;
    void *boss;
    int param;
    int cur;
    char *pl;
    char *bl;
    float d;
    int pressed;
    int one;
    int ma;
    int mb;
    int on;

    player = GAMEUTIL_get_player_obj();
    boss = GAMEUTIL_get_boss_obj();
    param = get_boss_subjective_camera_lws_animation_param();
    if (player == 0 || boss == 0 || param == 0)
        return;
    cur = get_main_type_camera_lws_animation();
    pl = GetLayoutClass(player);
    bl = GetLayoutClass(boss);
    d = distXZsq(*(void **)(pl + 0x134), *(void **)(bl + 0x134));
    pressed = 0;
    one = 1;
    ma = one << gcGlobalVar.btnA;
    on = padManagerData.on;
    if (((on & ma) && (padManagerData.trg & (one << gcGlobalVar.btnB)))
        || ((padManagerData.trg & ma) && (on & (one << gcGlobalVar.btnB))))
        pressed = 1;
    if (cur != 0 && param == get_camera_lws_animation_param(cur)) {
        if (pressed == 1)
            goto end;
        if (farDist * farDist < d)
            goto end;
        if (bossCamOk(boss))
            return;
    end:
        end_camera_lws_animation_by_paramID(param);
        return;
    } else if (pressed == 1) {
        if (d < nearDist * nearDist) {
            if (bossCamOk(boss)) {
                boot_camera_lws_animation_by_script(param);
                return;
            }
        }
        sePlaySystemSound(SeList_beep_test);
        return;
    }
}
