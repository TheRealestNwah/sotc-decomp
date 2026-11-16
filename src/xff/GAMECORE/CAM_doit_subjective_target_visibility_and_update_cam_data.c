/* Parked: 122 diffs, 136 words vs 141. Subjective camera visibility update: collision probe (func_000DD1C8), camera state checks, cross-position coefficient and a VU0 lerp (qmtc2 t, vsubx.w, vmulax/vmaddw) between p2+0x60 and the context into the work vector, then func_000DD3A8 and the status manager. Args: (c, a1, p2, a3, t0, t1, f12, f13). Remaining: the Original spills a1, t0 and the camera field to sp+0x48/0x4C/0x50 and reloads them (5 words), keeps p2+0x60 in s3 from the prologue and the literal 1 in s4; volatile fields for the spills gave 128. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern char *get_game_camera(int);
extern void *memset(void *, int, unsigned int);
extern int func_000DD1C8(void *, int, char *, char *, int, int);
extern void GAMEUTIL_set_data_by_dynamics_collision_info(char *, void *, int);
extern int is_reset_or_lws_fixed_point_or_lws_movie_or_cutout_game_camera(char *);
extern int is_must_reach_normal_default_angle(char *, char *);
extern int GAMEUTIL_get_cross_position_coefficient_t_by_dist_factor(float *, float *, int, char *, float, char *);
extern int GAMEUTIL_is_nearly_equal_zero(float, float);
extern void GAMEUTIL_reset_collision_info(char *);
extern void func_000DD3A8(int, char *, char *, int, int, void *, int);
extern void GAMEUTIL_doit_status_manager(char *, int, int, float);

int CAM_doit_subjective_target_visibility_and_update_cam_data(char *c, int a1, char *p2, int a3, int t0, int t1, float f12, float f13)
{
    struct {
        Vec v;
        char info[0x30];
        float t;
        float u;
    } L __attribute__((aligned(16)));
    char *cam;
    int cam1360;
    int r;

    cam = get_game_camera(t1);
    cam1360 = *(int *)(cam + 0x1360);
    memset(&L.v, 0, 0x10);
    *(int *)(c + 0x130) = 0;
    L.v.w = 1.0f;
    if (func_000DD1C8(L.info, a1, p2, c, a3, t1) != 1) {
        GAMEUTIL_set_data_by_dynamics_collision_info(c + 0xB0, L.info, 0);
        if (is_reset_or_lws_fixed_point_or_lws_movie_or_cutout_game_camera(cam) == 0
            && (*(int *)(cam + 0x1360) != 1 || is_must_reach_normal_default_angle(p2, cam) == 0)
            && *(int *)(c + 0x44) == 0) {
            r = GAMEUTIL_get_cross_position_coefficient_t_by_dist_factor(&L.t, &L.u, t0, c, f12, p2 + 0x60);
            if (r == 1) {
                if (GAMEUTIL_is_nearly_equal_zero(L.t - 1.0f, 0.001f) == r) {
                    L.v.q = *(s128 *)(p2 + 0x60);
                } else {
                    __asm__ __volatile__("qmtc2.ni %0, vf7\n"
                                         "lqc2 vf5, 0x0(%1)\n"
                                         "lqc2 vf6, 0x0(%2)\n"
                                         "vsubx.w vf8, vf0, vf7x\n"
                                         "vmulax.xyz ACC, vf5, vf7x\n"
                                         "vmaddw.xyz vf5, vf6, vf8w\n"
                                         "sqc2 vf5, 0x0(%3)\n"
                                         :
                                         : "r"(*(int *)&L.t), "r"(p2 + 0x60), "r"(c), "r"(&L.v)
                                         : "memory");
                }
                *(int *)(c + 0x130) = 1;
            }
        }
        if (*(int *)(c + 0x130) == 0 && *(int *)(c + 0x44) == 0)
            *(int *)(c + 0x44) = 2;
    } else {
        GAMEUTIL_reset_collision_info(c + 0xB0);
        *(int *)(c + 0x44) = 0;
    }
    func_000DD3A8(a1, c, p2, cam1360, *(int *)(c + 0x130), &L.v, t1);
    GAMEUTIL_doit_status_manager(c + 0x34, *(int *)(c + 0x44), 0, f13);
    return *(int *)(c + 0x130);
}
#endif
