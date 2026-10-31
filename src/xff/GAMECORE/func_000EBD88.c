extern void GAMEUTIL_constructor_col_plane_info(void *);
extern void GAMEUTIL_set_col_plane_info(void *, void *);
extern void *CAM_get_ground_contact_obj(void *);

static void func_000EBD88(char *c, char *o)
{
    int k = *(int *)(o + 0x1360);
    int z;

    if (k == 0 || k == 8)
        z = 1;
    else
        z = 0;
    if (z == 1)
        GAMEUTIL_constructor_col_plane_info(c + 0x1440);
    else
        GAMEUTIL_set_col_plane_info(c + 0x1440, CAM_get_ground_contact_obj(c + 0x23C));
}
