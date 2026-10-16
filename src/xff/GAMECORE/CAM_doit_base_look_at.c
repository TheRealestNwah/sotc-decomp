extern int is_reset_or_lws_movie_or_cutout_game_camera(void *);
extern void func_000DED78(void *, void *, int, float);
extern void func_000E2030(void *, void *, void *);

void CAM_doit_base_look_at(void *a, void *b, void *cam, void *d, float t)
{
    func_000DED78(a, b, is_reset_or_lws_movie_or_cutout_game_camera(cam), t);
    func_000E2030(a, b, d);
}
