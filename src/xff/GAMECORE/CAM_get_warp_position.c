#ifdef NONMATCHING
/* 115 diffs, 4 words shorter (141 vs 145). Draft from the asm; callee prototypes are guesses from the call sites. Semantics: probe the camera path from two candidate points (a3 then a4) against the collision world; on a hit convert it to collision dynamics and re-aim via get_camera_position_float_by_hit_collision (ok = 1), copy the result into *out (and into dynOut if given); otherwise, when mode == 1, fall back to check_camera_position_float_by_collision; finally, if the camera record (get_game_camera(a5)+0x10) has +4 == 1, take its +0x20 position and set +0x30. The Original holds a3/t0/t1/t2/t3/a1/a2 in s3/s5/s1/s4/s6/s7/s0 and ok in s2; ours picks a different order, which shifts every later register. The locals are one struct (dyn[3], p30, res40, res90) so the stack layout matches (frame 0x150 not yet). Permuter (12 workers, 25 min): 2725 -> 1535 only. */
typedef int s128 __attribute__((mode(TI)));

extern char *get_game_camera(void *);
extern int camera_collision_check_direct(void *, void *, void *, void *, int, int, void *, int);
extern void ConvertFromCollisionPointToDynamics(void *, void *);
extern void get_camera_position_float_by_hit_collision(void *, void *, void *, float, float, void *, void *, void *, int);
extern void CopyCollisionDynamics(void *, void *);
extern int check_camera_position_float_by_collision(void *, void *, void *, float, float, void *, void *, void *, int);

int CAM_get_warp_position(s128 *out, void *dynOut, s128 *pos, void *a3, void *a4, void *a5, void *a6, void *a7, float f0, float f1, int mode)
{
    struct {
        s128 dyn[3];
        s128 p30;
        char res40[0x50];
        char res90[0x50];
    } L;
    char *fp;
    int ok;
    int none;

    fp = get_game_camera(a5) + 0x10;
    ok = 0;
    L.p30 = *pos;
    if (!camera_collision_check_direct(L.res40, a4, a3, a5, 1, 0, a6, 1)) {
        none = camera_collision_check_direct(L.res90, a3, &L.p30, a5, 1, 0, a6, 1) == 0;
        if (!none) {
            ConvertFromCollisionPointToDynamics(L.dyn, L.res90);
            if (!none) {
                get_camera_position_float_by_hit_collision(L.dyn, a3, L.dyn, f0, f1, a7, a5, a6, 1);
                ok = 1;
            }
        }
    }
    if (ok == 0) {
        none = camera_collision_check_direct(L.res90, a4, &L.p30, a5, 1, 0, a6, 1) == 0;
        if (!none) {
            ConvertFromCollisionPointToDynamics(L.dyn, L.res90);
            if (!none) {
                get_camera_position_float_by_hit_collision(L.dyn, a4, L.dyn, f0, f1, a7, a5, a6, 1);
                ok = 1;
            }
        }
    }
    if (ok == 1) {
        *out = L.dyn[0];
        if (dynOut != 0)
            CopyCollisionDynamics(dynOut, L.dyn);
        else
            goto after;
    } else if (mode == 1) {
        ok = check_camera_position_float_by_collision(out, dynOut, a7, f0, f1, a5, a6, &L.p30, 1);
    }
after:
    if (*(int *)(fp + 4) == 1) {
        ok = 1;
        *out = *(s128 *)(fp + 0x20);
        *(int *)(fp + 0x30) = 1;
    }
    return ok;
}
#endif
