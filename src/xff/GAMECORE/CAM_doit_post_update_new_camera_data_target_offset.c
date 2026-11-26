/* riding/blocked are pinned to s7/s6. vdist and vdotf move their result to an FPR
 * inside the asm (like other matched VU0 helpers), vdotf into $f0; vdot pins its
 * operands to a0/v1; the reset 1.0f store goes through $f1. */
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

static inline float vdot(void *a0, void *b0)
{
    register void *a asm("$4") = a0;
    register void *b asm("$3") = b0;
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

static inline float vdotf(void *a, void *b)
{
    register float r asm("$f0");
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vaddw.x vf7, vf0, vf0w\n"
                         "vmul.xyz vf6, vf5, vf6\n"
                         "vaddax.x ACC, vf0, vf6x\n"
                         "vmadday.x ACC, vf7, vf6y\n"
                         "vmaddz.x vf6, vf7, vf6z\n"
                         "qmfc2.ni $2, vf6\n"
                         "mtc1 $2, %0\n"
                         : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
    return r;
}

static inline float vdist(void *a, void *b)
{
    float r;
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)
"
                         "lqc2 vf6, 0x0(%2)
"
                         "vsub.xyzw vf7, vf5, vf6
"
                         "vmul.xyz vf7, vf7, vf7
"
                         "vmulax.w ACC, vf0, vf7x
"
                         "vmadday.w ACC, vf0, vf7y
"
                         "vmaddz.w vf7, vf0, vf7z
"
                         ".word 0x4BA703BD
"
                         "vwaitq
"
                         "cfc2.ni $2, $vi22
"
                         "mtc1 $2, %0
"
                         : "=f"(r) : "r"(a), "r"(b) : "$2", "memory");
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
        { register float o asm("$f1") = 1.0f; *(float *)(ctl + 0x180) = o; }
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
    register int riding __asm__("$23");
    int obj;
    register int blocked __asm__("$22");
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
        if (GAMEUTIL_check_and_get_normalize_vector(&L.dir, &L.len, &L.dir) != 1 || vdotf(&L.dyn[1], &L.dir) <= 0.0f) {
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
