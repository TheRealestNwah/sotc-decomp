/* Parked attempt, 4 diffs, same size. Builds the look direction for the subjective camera by mode. Remaining: case 5 swaps f0/f1 for the 0xE0/0xE4 loads. */
#ifdef NONMATCHING
typedef int s128 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(8))) V;

extern int GAMEUTIL_check_and_get_normalize_vector(float *, int, float *);
extern int GAMEUTIL_get_boss_interest_position(V *, int);
extern int GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);
extern float GAMEUTIL_increase_yaw(float, float, int);
extern float GAMEUTIL_increase_pitch(float, float, float, float, int, int);
extern void GAMEUTIL_get_direction_by_yaw_pitch(float *, float, float);
extern void GAMEUTIL_convert_from_lw_to_game_coord(void *);
extern void GAMEUTIL_get_add_cur_stage_ofst_position(void *, void *);
extern int GAMEUTIL_is_yaw_pitch_get_direction(float *);

static inline void vecSub(float *out, void *a, void *b)
{
    __asm__ __volatile__("lqc2 vf5, 0x0(%1)\n"
                         "lqc2 vf6, 0x0(%2)\n"
                         "vsub.xyz vf5, vf5, vf6\n"
                         "sqc2 vf5, 0x0(%0)\n"
                         : : "r"(out), "r"(a), "r"(b) : "memory");
}

static void func_000EA508(float *dir, float *pos, char *mode, char *cam)
{
    V buf;
    V tmp;
    float yaw;
    V *bp;
    float pitch;
    float *yp;
    int ok = 0;
    int t = *(int *)(mode + 0xDC);

    if (t == 1) {
        vecSub(dir, pos, cam + 0x60);
        if (GAMEUTIL_check_and_get_normalize_vector(dir, 0, dir) == 1)
            ok = 1;
    } else if (t == 2 || t == 3) {
        if (GAMEUTIL_get_boss_interest_position(&buf, 1) == 1) {
            yp = &yaw;
            vecSub(dir, &buf, pos);
            if (GAMEUTIL_check_and_get_normalize_vector(dir, 0, dir) == 1
                && GAMEUTIL_get_yaw_pitch_by_direction(yp, &pitch, dir) == 1) {
                if (*(int *)(mode + 0xDC) == 3)
                    pitch = *(float *)(cam + 0xF34);
                ok = 1;
                yaw = GAMEUTIL_increase_yaw(yaw, *(float *)(mode + 0xE0) * 0.017453292519943295f, 0);
                pitch = GAMEUTIL_increase_pitch(pitch, *(float *)(mode + 0xE4) * 0.017453292519943295f,
                                                1.4835298641951802f, -1.4835298641951802f, 0, 0);
                GAMEUTIL_get_direction_by_yaw_pitch(dir, yaw, pitch);
            }
        }
    } else if (t == 4) {
        dir[0] = *(float *)(mode + 0xE0);
        dir[1] = *(float *)(mode + 0xE4);
        dir[2] = *(float *)(mode + 0xE8);
        dir[3] = 0.0f;
        GAMEUTIL_convert_from_lw_to_game_coord(dir);
        if (GAMEUTIL_check_and_get_normalize_vector(dir, 0, dir) == 1)
            ok = 1;
    } else if (t == 5) {
        tmp.x = *(float *)(mode + 0xE0);
        tmp.y = *(float *)(mode + 0xE4);
        tmp.z = *(float *)(mode + 0xE8);
        tmp.w = 1.0f;
        buf = tmp;
        GAMEUTIL_convert_from_lw_to_game_coord(bp = &buf);
        GAMEUTIL_get_add_cur_stage_ofst_position(bp, bp);
        vecSub(dir, &buf, pos);
        ok = GAMEUTIL_check_and_get_normalize_vector(dir, 0, dir) == 1;
    }
    if (ok == 1)
        ok = GAMEUTIL_is_yaw_pitch_get_direction(dir);
    if (ok == 0)
        *(s128 *)dir = *(s128 *)(cam + 0xF20);
}
#endif
