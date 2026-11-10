typedef struct {
    int b[0xDC / 4];
} Blk;

extern void *GAMEUTIL_get_motion_kind(void *);
extern void GAMEUTIL_reset_interp_ratio_cntrl(void *);
extern void GAMEUTIL_set_param_interp_ratio_cntrl(void *, float, float);
extern float GAMEUTIL_doit_interp_ratio_cntrl(void *, float);
extern void func_000E1820(void *);
extern void *GAMEUTIL_get_riding_horse_object(void *);
extern void *CAM_get_ground_contact_obj(void *);
extern int GAMEUTIL_is_floating_now(void *);
extern void GAMEUTIL_add_data_record_info(void *, int *);

void CAM_doit_target(char *cn, void *obj, float dt)
{
    char *s2;
    char *kind;
    int fl;

    *(void **)cn = obj;
    if (obj == 0)
        return;
    kind = GAMEUTIL_get_motion_kind(obj);
    if (kind != *(char **)(cn + 0x1E8)) {
        *(int *)(cn + 4) = 1;
        s2 = cn + 8;
        GAMEUTIL_reset_interp_ratio_cntrl(s2);
        if (*(int *)(cn + 0x108) != 0) {
            *(Blk *)(cn + 0x2C) = *(Blk *)(cn + 0x10C);
            *(int *)(cn + 0x28) = 1;
        } else {
            *(int *)(cn + 0x28) = 0;
        }
        *(char **)(cn + 0x1E8) = kind;
        if (kind != 0)
            *(Blk *)(cn + 0x1EC) = *(Blk *)kind;
    } else {
        *(int *)(cn + 4) = 0;
        s2 = cn + 8;
    }
    GAMEUTIL_set_param_interp_ratio_cntrl(s2, 0.0f, 1.0f);
    GAMEUTIL_doit_interp_ratio_cntrl(s2, dt);
    func_000E1820(cn);
    *(void **)(cn + 0x2C8) = GAMEUTIL_get_riding_horse_object(*(void **)cn);
    fl = GAMEUTIL_is_floating_now(CAM_get_ground_contact_obj(cn));
    GAMEUTIL_add_data_record_info(cn + 0x2CC, &fl);
}
