typedef unsigned int u_long128 __attribute__((mode(TI)));

typedef union {
    u_long128 q;
    float f[4];
} VecQ;

typedef struct {
    char pad[0x50];
} __attribute__((aligned(16))) WaterHit;

extern int GAMEUTIL_is_horse_obj_contact_ground(int *, void *);
extern char *GetLayoutClass(void *);
extern void *CAM_get_target_riding_obj(void *);
extern int player_collision_check_direct_water_surface_plus(void *, void *, void *, void *, void *, int);

static void func_000D7CE8(int *inWater, void *target, void *cam, void *player)
{
    WaterHit hit;
    VecQ start;
    VecQ end;
    int horse;

    horse = GAMEUTIL_is_horse_obj_contact_ground(0, target);
    end.q = start.q = **(u_long128 **)(GetLayoutClass(target) + 0x134);
    if (*inWater == 1) {
        if (horse == 1) {
            end.f[1] -= 2.0f;
        } else {
            end.f[1] -= 1.0f;
        }
    } else {
        if (horse == 1) {
            end.f[1] -= 3.5f;
        } else {
            end.f[1] -= 2.5f;
        }
    }
    *inWater = player_collision_check_direct_water_surface_plus(&hit, &start, &end, player, CAM_get_target_riding_obj(cam), 1) != 1;
}
