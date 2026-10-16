extern int GAMEUTIL_get_segment_num_and_data(int *, char *);
extern char *GetLayoutClass(void *);

typedef struct {
    int type;
    void *obj;
    char pad8[4];
    char *mode;
} CutoutSrc;

int get_cutout_mode_manager_segment_camera_place_status(int *out, CutoutSrc *s)
{
    int n = 0;
    char **p;
    int t = s->type;

    *out = 0;
    if (t == 1) {
        n = GAMEUTIL_get_segment_num_and_data(out, *(char **)(s->mode + 0x14) + 0x1C);
    } else if (t == 2) {
        p = *(char ***)(GetLayoutClass(s->obj) + 0x1A8);
        if (p != 0 && *p != 0)
            n = GAMEUTIL_get_segment_num_and_data(out, *p + 0x1C);
    }
    return n;
}
