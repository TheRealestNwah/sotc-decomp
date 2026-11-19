extern void func_000ED678(int *, int *);
extern void func_000EEA28(int *, int, int, int);
extern void func_000EED00(int *, int *, int *, int, float, float);
extern int func_000F2700(int *, int *);
#ifdef NONMATCHING
static void func_000F27A0(char *, char *, char *, char *, int, float);
#else
extern void func_000F27A0(char *, char *, char *, char *, int, float);
#endif
extern void func_000F2970(void *, int *, int);
extern void func_000F29C0(void *);
extern void func_000F2A40(int);
extern float get_interp_ratio_game_camera_param_manager(void *);
extern float get_interp_time_game_camera_param_manager(void *);
extern int is_reset_or_lws_movie_or_cutout_game_camera(int);

#ifdef NONMATCHING /* 75 diffs: call sequence, pointer pins ($s0 cp, $s2 cur, $s3 sel, $s4 prev, $s5/$s6 args) and control flow right; the compiler hoists the m+0x664 address above the first calls and loads *cp through it, the original keeps base+offset loads */
void doit_game_camera_param_manager(char *m, int a10, int a2, int a30, float dt)
{
    register int a1 __asm__("$22") = a10;
    register int a3 __asm__("$21") = a30;
    int sp0;
    float r;
    float inv;
    register int *cur __asm__("$18");
    register int *prev __asm__("$20");
    register int *sel __asm__("$19");
    register int *cp __asm__("$16");
    float t;

    cur = (int *)(m + 0x10);
    prev = (int *)(m + 0xCB8);
    sp0 = 0;
    func_000F2970(m + 0x130C, &sp0, a1);
    func_000F27A0(m, *(char **)(m + 0x664), (char *)sp0, (char *)a2, a3, dt);
    cp = (int *)(m + 0x664);
    sel = cp;
    if (sp0 != *(int *)(m + 0x664)) {
        func_000ED678(cur, prev);
        *(int *)m = 1;
        *(int *)(m + 0x664) = sp0;
    } else {
        *(int *)m = 0;
        cur = (int *)(m + 0x10);
        prev = (int *)(m + 0xCB8);
    }
    func_000EEA28(cp, sp0, a1, a3);
    if (is_reset_or_lws_movie_or_cutout_game_camera(a3) == 1) {
        t = get_interp_time_game_camera_param_manager(m);
        *(float *)(m + 4) = t;
    } else if (*(int *)m != 1) {
        *(float *)(m + 4) = *(float *)(m + 4) + dt;
    } else {
        *(float *)(m + 4) = 0.0f;
    }
    r = get_interp_ratio_game_camera_param_manager(m);
    inv = 1.0f - r;
    sel = *cur != 0 ? cur : cp;
    func_000ED678(prev, cp);
    func_000EED00(prev, sel, cp, func_000F2700(cp, sel), inv, r);
    func_000F29C0(m);
    func_000F2A40(a1);
}
#endif

#ifdef NONMATCHING /* 2 diffs: only the order of the two moves that copy the last two arguments into $t7/$t2 differs; a 400-iteration permuter run found nothing better */
extern int *DldSysUndefSymbol;
extern unsigned int *get_cutout_mode_manager_segment_camera_place_status(int *, void *);

static inline char *dldElem(unsigned int *h)
{
    unsigned int v = *h;
    int off = v & 0x3FFFF;
    char *t = off != 0 ? *(char **)((char *)h - off) : 0;
    return (t != 0 && t != (char *)DldSysUndefSymbol) ? *(char **)(t + 0x10) + ((v >> 18) & 0xFFF) * *(int *)(*(char **)(t + 8) + 0xC) : 0;
}

static void func_000F27A0(char *m, char *cur, char *next, char *seg, int cam, float dt)
{
    int n;
    unsigned int *list;
    int i;
    int j;
    unsigned int *e;

    n = 0;
    list = get_cutout_mode_manager_segment_camera_place_status(&n, seg + 0x1270);
    *(int *)(m + 8) = 0;
    if (list == 0 || is_reset_or_lws_movie_or_cutout_game_camera(cam) == 1) {
        *(float *)(m + 0xC) = 0.0f;
        return;
    }
    *(float *)(m + 0xC) += dt;
    if (*(float *)(m + 0xC) >= 1.0f && cur != next) {
        unsigned int *l;
        if (n <= 0) return;
        l = list;
        i = n;
        do {
            if (cur == dldElem(l)) {
                for (j = 0; j < 2; j++) {
                    e = l + 1 + j;
                    if (next == dldElem(e)) {
                        *(int *)(m + 8) = 1;
                        *(float *)(m + 0xC) = 0.0f;
                    }
                }
            }
            l += 3;
        } while (--i != 0);
    }
}
#endif
