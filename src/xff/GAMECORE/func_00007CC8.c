extern void *GAMEUTIL_get_riding_horse_object(void *);
extern void DEBUG_disp_collision_attribute_info_extend(void *, void *, float, float, float);

static void func_00007CC8(void *obj, void *col, float x, float y, float z)
{
    void *horse = GAMEUTIL_get_riding_horse_object(obj);

    if (horse)
        obj = horse;
    DEBUG_disp_collision_attribute_info_extend(obj, col, x, y, z);
}
