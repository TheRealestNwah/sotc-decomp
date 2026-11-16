/* Parked: 145 diffs, same size (180 words incl. the split tail func_0006F1F8). Horse-riding camera nudge: while the player rides, scales the relative movement (player minus horse position, then minus the stored previous vector at +0x1B0, VU0 vsub.xyz) into yaw/pitch offsets via GAMEUTIL_get_divide_vector_value, clamps each to +/-f21 (0.015 standing, 0.01 moving), flips yaw when +0x298 == 1, stores the vector back, then feeds both offsets to GAMEUTIL_increase_yaw/pitch (limits +/-85 degrees = 1.4835298) and GAMEUTIL_get_direction_by_yaw_pitch. Remaining: the Original keeps zero in f20 (shared with the yaw scale) and the 1 constant in s1, ours allocates f22/s0; the clamp blocks are scheduled differently. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    };
    s128 q;
} Vec;

extern int GAMEUTIL_get_riding_horse_object(int);
extern int GAMEUTIL_get_horse_move_status(void *, int);
extern int GAMEUTIL_is_player_obj_standing_on_horse(int);
extern char *GetLayoutClass(int);
extern void GAMEUTIL_get_divide_vector_value(float *, float *, int, void *, int, int, int);
extern float get_merge_yaw_nico_yaw_pitch_cntrl(void *);
extern float get_merge_pitch_nico_yaw_pitch_cntrl(void *);
extern float GAMEUTIL_increase_yaw(int, float, float);
extern float GAMEUTIL_increase_pitch(int, int, float, float, float, float);
extern void GAMEUTIL_get_direction_by_yaw_pitch(int, float, float);

static void func_0006EF28(int dst, char *w, int p2, int p3, int p4)
{
    struct {
        Vec d;
        Vec p;
        Vec q;
        int one;
        float yaw;
        float pitch;
    } L __attribute__((aligned(16)));
    int horse;
    int st;
    float f20;
    float f21;
    float f22;
    float yaw;

    f20 = 0.0f;
    L.yaw = 0.0f;
    L.pitch = 0.0f;
    horse = GAMEUTIL_get_riding_horse_object(*(int *)(w + 4));
    if (horse != 0) {
        L.one = 1;
        f22 = 0.0f;
        st = GAMEUTIL_get_horse_move_status(&L.one, horse);
        f21 = f22;
        if (GAMEUTIL_is_player_obj_standing_on_horse(*(int *)(w + 4)) == 1) {
            f20 = 2.0f;
            f22 = 0.29999998f;
            f21 = 0.015f;
        } else if (st == 1) {
            f22 = 0.19999999f;
            f21 = 0.01f;
            f20 = f22;
        }
        if (0.0f < f21) {
            L.p.q = *(s128 *)*(char **)(GetLayoutClass(*(int *)(w + 4)) + 0x134);
            __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                 "lqc2 vf6, 0x0(%2)\n"
                                 "vsub.xyz vf5, vf5, vf6\n"
                                 "sqc2 vf5, 0x0(%0)\n"
                                 :
                                 : "r"(&L.d), "r"(&L.p), "r"(*(char **)(GetLayoutClass(horse) + 0x134))
                                 : "memory");
            if (*(int *)(w + 0x1A4) == 1) {
                __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                                     "lqc2 vf6, 0x0(%2)\n"
                                     "vsub.xyz vf5, vf5, vf6\n"
                                     "sqc2 vf5, 0x0(%0)\n"
                                     :
                                     : "r"(&L.q), "r"(&L.d), "r"(w + 0x1B0)
                                     : "memory");
                GAMEUTIL_get_divide_vector_value(&L.yaw, &L.pitch, 0, &L.q, p2, p3, p4);
                L.yaw = L.yaw * f20;
                L.pitch = L.pitch * f22;
                if (L.yaw < 0.0f ? f21 < -L.yaw : f21 < L.yaw)
                    L.yaw = (0.0f <= L.yaw) ? f21 : -f21;
                if (L.pitch < 0.0f ? f21 < -L.pitch : f21 < L.pitch)
                    L.pitch = (0.0f <= L.pitch) ? f21 : -f21;
                if (*(int *)(w + 0x298) == 1)
                    L.yaw = -L.yaw;
            }
            *(int *)(w + 0x1A4) = 1;
            *(s128 *)(w + 0x1B0) = L.d.q;
        } else {
            *(int *)(w + 0x1A4) = 0;
        }
    } else {
        *(int *)(w + 0x1A4) = 0;
    }
    yaw = GAMEUTIL_increase_yaw(0, get_merge_yaw_nico_yaw_pitch_cntrl(w + 0xC), L.yaw);
    GAMEUTIL_get_direction_by_yaw_pitch(dst, yaw, GAMEUTIL_increase_pitch(0, 0, get_merge_pitch_nico_yaw_pitch_cntrl(w + 0xC), L.pitch, 1.4835298f, -1.4835298f));
}
#endif
