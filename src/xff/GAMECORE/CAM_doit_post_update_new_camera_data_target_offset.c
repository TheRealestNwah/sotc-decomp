/* Parked: 25 diffs, same size. Remaining: callee-saved rotation of col/riding/blocked (fp/s7/s6), f0/f1 swaps in the reset 1.0f store and the normalize-check compare, late mtc1 after the vdist cfc2, v1/a0 swap in the last vdot operands. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

extern s128 ZeroPoint;
extern s128 ZUnitVector;
extern void ConvertFromCollisionPointToDynamics(void *, void *);
extern int GAMEUTIL_check_and_get_normalize_vector(void *, float *, void *);
extern void GAMEUTIL_doit_status_manager(void *, int, int, float);
extern int GAMEUTIL_get_cur_status_status_manager(void *);
extern float GAMEUTIL_get_dist_ratio(float, float, float);
extern float GAMEUTIL_get_object_move_noise_square(int);
extern float GAMEUTIL_get_status_continue_time_status_manager(void *);
extern void GAMEUTIL_reset_status_manager(void *, int);
extern char *GetLayoutClass(int);
extern int camera_collision_check_direct(void *, void *, void *, void *, int, int, int, int);
extern void doit_double_spring_interp_cntrl(void *, int, float, float);
extern float iosGetCosf(float);
extern int is_reset_or_lws_movie_or_cutout_game_camera(int);
extern void reset_double_spring_interp_cntrl(void *, float);

static inline void vsub(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline void vadd(void *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vadd.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static inline float vdot(void *a, void *b)
{
    register float r asm("$2");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni %0, vf6\n"
                         : "=r"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

static inline float vdist(void *a, void *b)
{
    register float r asm("$2");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vmulax.w ACC, vf0, vf7x\n"
                         "vmadday.w ACC, vf0, vf7y\n"
                         "vmaddz.w vf7, vf0, vf7z\n"
                         ".word 0x4BA703BD\n"
                         "vwaitq\n"
                         "cfc2.ni %0, $vi22\n"
                         : "=r"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

static inline float vdistsq(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyzw vf7, vf5, vf6\n"
                         "vmul.xyz vf7, vf7, vf7\n"
                         "vaddy.x vf7, vf7, vf7y\n"
                         "vaddz.x vf7, vf7, vf7z\n"
                         "qmfc2.ni %0, vf7\n"
                         : "=r"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

static inline int checkHit(void *dyn, char *hit, void *from, void *to, void *col, int flag, int riding)
{
    int miss = camera_collision_check_direct(hit, from, to, col, flag, 0, riding, 1) == 0;
    if (!miss)
        ConvertFromCollisionPointToDynamics(dyn, hit);
    return miss;
}

static inline void resetit(char *ctl)
{
        reset_double_spring_interp_cntrl(ctl + 0x160, 1.0f);
        *(float *)(ctl + 0x180) = 1.0f;
        GAMEUTIL_reset_status_manager(ctl + 0x184, 0);
        *(s128 *)(ctl + 0x1A0) = ZeroPoint;
        *(s128 *)(ctl + 0x1B0) = ZUnitVector;
        }

void CAM_doit_post_update_new_camera_data_target_offset(char *ctl, char *cam, int a2, void *col, float f)
{
    struct { s128 dyn[3]; s128 diff; s128 to; s128 from; s128 dir; char hit[0x50]; char hit2[0x50]; float len; } L;
    char *src;
    char *sub;
    int one;
    int r;
    int riding;
    int obj;
    int blocked;
    float ratio;
    int miss;
    int st;
    int force;
    char *sm;
    float noise;
    float cosv;
    float one1;

    r = is_reset_or_lws_movie_or_cutout_game_camera(a2);
    one = 1;
    __asm__("" : "+r"(one));
    if (r == one) {
        resetit(ctl);
        return;
    }
    src = cam + 0xE0;
    sub = cam + 0x23C;
    obj = *(int *)sub;
    riding = *(int *)(sub + 0x2C8);
    blocked = 0;
    ratio = 1.0f;
    vsub(&L.diff, ctl + 0x60, ctl + 0x30);
    vadd(&L.to, cam + 0xF0, &L.diff);
    vadd(&L.from, src, &L.diff);
    L.dir = *(s128 *)(src + 0x20);
    L.len = *(float *)(src + 0x38);
    if (!checkHit(L.dyn, L.hit, src, &L.from, col, 1, riding)) {
        L.from = L.dyn[0];
        vsub(&L.dir, &L.to, &L.from);
        if (GAMEUTIL_check_and_get_normalize_vector(&L.dir, &L.len, &L.dir) != 1 || vdot(&L.dyn[1], &L.dir) <= 0.0f) {
            ratio = 0.0f;
            blocked = 1;
        }
    }
    if (!blocked) {
        miss = checkHit(L.dyn, L.hit2, &L.from, &L.to, col, 0, riding);
        ratio = 1.0f;
        if (miss != 1)
            ratio = GAMEUTIL_get_dist_ratio(vdist(&L.from, L.dyn), L.len * 0.39999998f, L.len);
    }
    st = 1;
    one1 = 1.0f;
    if (ratio < one1) {
        *(s128 *)(ctl + 0x1A0) = **(s128 **)(GetLayoutClass(obj) + 0x134);
        *(s128 *)(ctl + 0x1B0) = *(s128 *)(src + 0x20);
        if (ratio < *(float *)(ctl + 0x180))
            *(float *)(ctl + 0x180) = ratio;
        force = 1;
        sm = ctl + 0x184;
    } else {
        sm = ctl + 0x184;
        if (GAMEUTIL_get_cur_status_status_manager(sm) == 0)
            goto reset;
        noise = GAMEUTIL_get_object_move_noise_square(obj);
        cosv = iosGetCosf(0.34906587f);
        if (GAMEUTIL_get_status_continue_time_status_manager(sm) > one1) {
            if (vdistsq(ctl + 0x1A0, *(void **)(GetLayoutClass(obj) + 0x134)) > noise)
                goto reset;
            if (vdot(ctl + 0x1B0, src + 0x20) < cosv)
                goto reset;
        }
        force = 0;
        goto done;
    reset:
        *(float *)(ctl + 0x180) = one1;
        st = 0;
        force = 0;
    }
done:
    GAMEUTIL_doit_status_manager(sm, st, force, f);
    doit_double_spring_interp_cntrl(ctl + 0x160, 0, *(float *)(ctl + 0x180), f);
}
#endif
