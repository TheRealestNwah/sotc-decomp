extern int is_reset_or_lws_movie_or_cutout_game_camera(void *);
static void func_000E2118(void *, int *, int, int, float);
static void func_000E2178(void *, int *, int, float);

void CAM_doit_look_at_spring(void *a, int *b, void *c, float f)
{
    int r = is_reset_or_lws_movie_or_cutout_game_camera(c);
    func_000E2118(a, b, *b, r, f);
    func_000E2178(a, b, r, f);
}
