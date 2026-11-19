/* Parked attempt: 17 words differ from the Original. */
#ifdef NONMATCHING
extern int GAMEUTIL_get_pre_status_status_manager(void *);
extern int GAMEUTIL_get_cur_status_status_manager(void *);
extern int is_reset_or_lws_movie_game_camera(void *);
extern void GAMEUTIL_reset_position_filter(void *, void *);
extern int *GAMEUTIL_get_data_record_info(void *, int);
extern float GAMEUTIL_get_object_move_noise(void *);
extern void GAMEUTIL_set_parameter_position_filter(void *, float);
extern int GAMEUTIL_doit_position_filter(void *, void *, int);

static inline int anyRecord(char *rec)
{
    int n = 2;
    int i;

    if (*(int *)(rec + 0xC) < n)
        n = *(int *)(rec + 0xC);

    for (i = 0; i < n; i++) {
        if (*GAMEUTIL_get_data_record_info(rec, i) == 1)
            return 1;
    }
    return 0;
}

static void func_000DCE28(char *ctx, void *pos, char *cam, void *arg)
{
    char *sm = ctx + 0x34;
    char *c = cam + 0x23C;
    int flag;
    int st;

    if ((GAMEUTIL_get_pre_status_status_manager(sm) && !GAMEUTIL_get_cur_status_status_manager(sm)) || *(int *)(ctx + 0x130) == 1)
        *(int *)(ctx + 0x30) = 1;
    if (is_reset_or_lws_movie_game_camera(arg) == 1) {
        GAMEUTIL_reset_position_filter(ctx, pos);
        *(int *)(ctx + 0x30) = 0;
        return;
    }
    st = GAMEUTIL_get_cur_status_status_manager(sm);
    flag = st == 0;
    if (flag == 0 || anyRecord(c + 0x2CC) == 1)
        flag = 1;
    GAMEUTIL_set_parameter_position_filter(ctx, GAMEUTIL_get_object_move_noise(*(void **)c));
    if (GAMEUTIL_doit_position_filter(ctx, pos, flag) == 1)
        *(int *)(ctx + 0x30) = 0;
}
#endif
