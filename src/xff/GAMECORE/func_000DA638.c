extern void *CAM_get_target_riding_obj(void *);
extern int player_collision_check_direct_water_surface_plus(void *, void *, void *, void *, void *, int);

static int func_000DA638(void *a, void *b, void *c, char *cam, void *e)
{
    return player_collision_check_direct_water_surface_plus(a, b, c, e, CAM_get_target_riding_obj(cam + 0x23C), 1);
}
