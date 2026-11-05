extern char *get_cur_using_lws_anime_mode_base_class(void *);
extern int is_reset_or_lws_movie_or_cutout_game_camera(void *);
extern void reset_time_interp_param_camera_dist_to_look_at(char *);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_interp_value(float, float, float);

static inline float vecDist(void *a, void *b)
{
    float d;

    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         "vsqrt Q, vf7w\n"
                         "vwaitq\n"
                         "cfc2 $2, $vi22\n"
                         "mtc1 $2, %0\n"
                         : "=f"(d) : "r"(a), "r"(b) : "$2");
    return d;
}

static float func_000D78F8(char *cam, char *b, void *c, float dt)
{
    char *base;
    float r;

    base = get_cur_using_lws_anime_mode_base_class(c);
    if (is_reset_or_lws_movie_or_cutout_game_camera(c) == 1)
        reset_time_interp_param_camera_dist_to_look_at(cam);
    if (base) {
        r = vecDist(base + 0x230, base + 0x240);
    } else {
        *(float *)(cam + 0x74) += dt;
        r = GAMEUTIL_get_dist_ratio(*(float *)(cam + 0x74), 0, *(float *)(cam + 0x70));
        r = GAMEUTIL_get_interp_value(*(float *)(b + 0x30), *(float *)(cam + 0x78), r);
    }
    return r;
}
