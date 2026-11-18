extern void *CAM_get_target_obj(void *);
extern float GAMEUTIL_get_object_move_noise(void *);
extern void *is_this_camera_region_alive(void *, int);
extern int get_region_type_camera_region(void *);
extern float get_hit_region_ofst_camera_region(void *);
extern void GAMEUTIL_set_parameter_col_plane_info_filter(char *, float, float);
extern void GAMEUTIL_doit_col_plane_info_filter(char *, char *, float);
extern void *get_camera_obj(void *);
extern int GAMEUTIL_is_boss_booting(void);
extern void *get_apply_camera_region(void *, int, unsigned long, void *, void *, int);
extern int get_priority_camera_region(void *);
extern float get_change_grace_time_camera_region(void *);
extern int get_manage_object_id_camera_region(void *);

static void func_000D8E80(char *c, char *cam, void *x, float dt)
{
    void *tgt = CAM_get_target_obj(cam + 0x15AC);
    float noise = GAMEUTIL_get_object_move_noise(tgt);
    char *f;
    void *reg;
    int change;

    *(void **)(c + 0xC) = is_this_camera_region_alive(*(void **)(c + 0xC), *(int *)(c + 0x10));
    if (get_region_type_camera_region(*(void **)(c + 0xC)) == 1 && noise < get_hit_region_ofst_camera_region(*(void **)(c + 0xC)))
        noise = get_hit_region_ofst_camera_region(*(void **)(c + 0xC));
    f = c + 0xD0;
    GAMEUTIL_set_parameter_col_plane_info_filter(f, noise, 2.0f);
    GAMEUTIL_doit_col_plane_info_filter(f, cam + 0x27B0, dt);
    {
        void *co = get_camera_obj(x);

        change = 1;

        reg = get_apply_camera_region(tgt, *(int *)(f + 8), *(unsigned long *)(f + 0x10), *(void **)(c + 0xC), co, GAMEUTIL_is_boss_booting());
    }
    if (*(void **)(c + 0xC) != 0 && *(void **)(c + 0xC) != reg) {
        if (get_priority_camera_region(*(void **)(c + 0xC)) >= get_priority_camera_region(reg)) {
            *(float *)(c + 0x14) += dt;
            if (*(float *)(c + 0x14) <= get_change_grace_time_camera_region(*(void **)(c + 0xC)))
                change = 0;
        }
    }
    if (change == 1) {
        *(void **)(c + 0xC) = reg;
        *(float *)(c + 0x14) = 0.0f;
    }
    if (*(void **)(c + 0xC) != 0)
        *(int *)(c + 0x10) = get_manage_object_id_camera_region(*(void **)(c + 0xC));
    else
        *(int *)(c + 0x10) = -1;
}

