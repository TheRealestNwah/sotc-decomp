#ifdef NONMATCHING
/* 124 diffs, 25 words short (127 vs 152). Draft from the asm. w[0] is the tracked obstacle id, w[1]/w[2] a distance and a timer, w[3] a "closer than before" flag, w[4] a running maximum. The scan asks func_000E1FA8 for a count and an id list (stack: n, ids[1], hit[1]), re-measures the tracked id, or adopts the first id when slot 0 is free. Differences: the Original keeps 0.0f in $f21 across the loop, indexes ids by a running sll offset (s7 = &ids, fp = &hit) with a "found" flag in $a1, and uses a 0x70 frame with s0-s7/fp saved; ours uses 0x50. Not yet permuted. */
extern int is_reset_or_lws_movie_or_cutout_game_camera(void *);
extern void func_000E1FA8(int *n, int *ids);
extern char *GetLayoutClass(int, int);
extern float func_000E1ED8(int, char *, char *, void *);

void CAM_doit_obstacle_avoid_cntrl(int *w, void *a1, void *a2, float dt)
{
    struct {
        int n;
        int ids[1];
        int hit[1];
    } L;
    float *wf = (float *)w;
    int i;

    if (is_reset_or_lws_movie_or_cutout_game_camera(a2) == 1) {
        w[4] = 0;
        w[0] = 0;
        w[1] = 0;
        w[2] = 0;
        w[3] = 0;
        return;
    }
    L.n = 0;
    L.hit[0] = 0;
    func_000E1FA8(&L.n, L.ids);
    for (i = 0; i < L.n; i++) {
        int found = 0;

        if (w[0] == L.ids[i]) {
            char *lc = GetLayoutClass(w[0], 0);
            char *s1 = *(char **)(*(char **)(lc + 0x1A8) + 4);
            float f2 = func_000E1ED8(w[0], lc, s1, a1);

            if (!(0.0f < wf[1]) || wf[1] <= f2) {
                wf[1] = f2;
                w[2] = 0;
            } else if (*(float *)(s1 + 0x28) <= f2) {
                w[2] = 0;
            } else {
                wf[2] += dt;
                if (*(float *)(s1 + 0x2C) < wf[2])
                    wf[1] = f2;
            }
            L.hit[0] = 1;
            found = 1;
        }
        if (!found) {
            int j;
            int *s = w;

            for (j = 0; j <= 0; j++, s += 3) {
                if (s[0] == 0) {
                    int id = L.ids[i];
                    char *lc = GetLayoutClass(id, 0);

                    s[0] = id;
                    ((float *)s)[1] = func_000E1ED8(id, lc, *(char **)(*(char **)(lc + 0x1A8) + 4), a1);
                    s[2] = 0;
                    L.hit[j] = 1;
                    break;
                }
            }
        }
    }
    if (L.hit[0] == 0) {
        w[0] = 0;
        w[1] = 0;
        w[2] = 0;
    }
    w[4] = 0;
    {
        float cur = wf[1];
        float mx = wf[4];
        float old = mx;

        if (mx < cur) {
            wf[4] = cur;
            mx = cur;
        }
        w[3] = old < mx;
    }
}
#endif
