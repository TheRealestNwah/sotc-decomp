extern void *CAM_get_ground_contact_obj(void *);
extern int GAMEUTIL_is_boss_obj(void *, int);

int is_must_reach_normal_default_angle(char *c)
{
    if (GAMEUTIL_is_boss_obj(CAM_get_ground_contact_obj(c + 0x23C), 1) == 1 || *(int *)(*(char **)c + 4) == 2) return 1;
    return 0;
}
