/* Parked: 4 diffs, same size. The Original addresses cand[best] as lq 0x50(&L + best*16) with &L (sp+0x10) in a register,
 * so cand sits 0x50 past L in one frame block; an empty asm barrier keeps &L in a register here (the cand
 * offset depends on that frame layout). Hoisting &M.d / &M.ofs into pointers ahead of the loop (a permuter find)
 * gives the Original's loop-pointer setup order. Remaining: $a0/$v1 swapped in the final cand[best] copy. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct { float v[3]; } F3;

extern void *CAM_get_target_obj(void *);
extern void *CAM_get_target_riding_obj(void *);
extern char *GetLayoutClass(void *);
extern void *memset(void *, int, unsigned int);
extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, void *);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(void *, float, float);
extern int camera_collision_check_direct(void *, void *, void *, void *, int, int, void *, int);
extern void ConvertFromCollisionPointToDynamics(void *, void *);
extern int CAM_get_warp_position(void *, void *, void *, void *, void *, void *, void *, void *, float, float, int);

static inline int checkHit(void *dyn, void *tgt, void *to, void *col, char *sub)
{
    char hit[0x50] __attribute__((aligned(16)));
    int miss;

    miss = camera_collision_check_direct(hit, tgt, to, col, 1, 0, CAM_get_target_riding_obj(sub), 1) == 0;
    if (!miss)
        ConvertFromCollisionPointToDynamics(dyn, hit);
    return miss;
}

void CAM_get_safety_cam_and_look_at_posi(void *out, s128 *cam, s128 *look, s128 *src, char *cm, void *col, int mode)
{
    struct {
        s128 pos;
        s128 tgt;
    } L;
    char *sub = cm + 0x23C;
    int best;
    int i;
    float len;
    float neg;

    L.tgt = **(s128 **)(GetLayoutClass(CAM_get_target_obj(sub)) + 0x134);
    *cam = *src;
    if (mode == 1) {
        float yaw[3] = { 0.0f, 3.14159250f, 0.0f };
        float pitch[3] = { 0.0f, 0.0f, -1.57079625f };
        float dist[3] = { 0 };
        s128 cand[3];
        struct {
            s128 dir;
            s128 dyn[3];
            s128 d;
            s128 ofs;
        } M;
        float y0;
        float p0;
        int miss;
        s128 *c;
        s128 *dp;
        s128 *op;

        best = -1;
        __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                             "lqc2 vf6, 0x0(%2)\n"
                             "vsub.xyz vf5, vf5, vf6\n"
                             "sqc2 vf5, 0x0(%3)\n"
                             "lqc2 vf7, 0x0(%3)\n"
                             "vmul.xyz vf7, vf7, vf7\n"
                             "vmulax.w ACC, vf0, vf7x\n"
                             "vmadday.w ACC, vf0, vf7y\n"
                             "vmaddz.w vf7, vf0, vf7z\n"
                             ".word 0x4BA703BD\n"
                             "vwaitq\n"
                             "cfc2.ni $2, $vi22\n"
                             "mtc1 $2, %0\n"
                             : "=f"(len) : "r"(cam), "r"(look), "r"(&M.dir) : "$2", "memory");
        {
            float inv = 1.0f / len;
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "qmtc2.ni %1, vf6\n"
                                 "vmulx.xyz vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 : : "r"(&M.dir), "r"(inv) : "memory");
        }
        neg = -len;
        GAMEUTIL_get_yaw_pitch_by_direction(&y0, &p0, &M.dir);
        dp = &M.d;
        op = &M.ofs;
        c = cand;
        for (i = 0; i < 3; i++, c++) {
            float y = GAMEUTIL_increase_yaw(0, y0, yaw[i]);
            GAMEUTIL_get_direction_by_yaw_pitch(dp, y, GAMEUTIL_increase_pitch(0, 0, p0, pitch[i], 1.48352981f, -1.48352981f));
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "qmtc2.ni %1, vf6\n"
                                 "vmulx.xyz vf5, vf5, vf6x\n"
                                 "sqc2 vf5, 0x0(%2)\n"
                                 : : "r"(dp), "r"(neg), "r"(op) : "memory");
            __asm__ __volatile__("lqc2 vf5, 0x0(%0)\n"
                                 "lqc2 vf6, 0x0(%1)\n"
                                 "vadd.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0x0(%2)\n"
                                 : : "r"(cam), "r"(op), "r"(c) : "memory");
            miss = checkHit(M.dyn, &L.tgt, c, col, sub);
            if (miss == 1) {
                best = i;
                break;
            }
            {
                float dd;
                __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                     "lqc2 vf6, 0x0(%2)\n"
                                     "vsub.xyzw vf7, vf5, vf6\n"
                                     "vmul.xyz vf7, vf7, vf7\n"
                                     "vaddy.x vf7, vf7, vf7y\n"
                                     "vaddz.x vf7, vf7, vf7z\n"
                                     "qmfc2.ni $2, vf7\n"
                                     "mtc1 $2, %0\n"
                                     : "=f"(dd) : "r"(&L.tgt), "r"(M.dyn) : "$2");
                dist[i] = dd;
            }
        }
        if (best < 0) {
            best = 0;
            for (i = 1; i < 3; i++)
                if (dist[best] < dist[i])
                    best = i;
        }
        { char *lp = (char *)&L; __asm__("" : "+r"(lp)); L.pos = ((s128 *)(lp + 0x50))[best]; }
    } else {
        L.pos = *look;
    }
    CAM_get_warp_position(out, 0, &L.pos, cam, &L.tgt, col, CAM_get_target_riding_obj(sub), cm + 0x1814, 0.1f, 0.4f, 1);
}
#endif
