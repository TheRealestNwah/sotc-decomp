typedef int s128 __attribute__((mode(TI)));

extern char B_00183B20[];
extern void *get_main_cameraman(void);
extern void get_camera_parameter_cameraman(float *, float *, float *, float *, void *);
extern void *get_camera_target_group(void *);
extern void *isysGroupForFirst(void *, int);
extern void *isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern int GAMEUTIL_is_player_obj(void *);
extern char *GetLayoutClass(void *);
extern void getStageAreaName(char *, void *);
extern char *username(void);
extern void iosGetClock(unsigned char *);
extern int iosSPrintf(char *, char *, ...);

static int func_00004868(char *out, char *tag)
{
    struct {
        int junk[4];
        char name[16];
        float p60[4];
        float p70[4];
        float p80[4];
        float p90[4];
        float pA0[2];
        unsigned char clk[8];
    } L __attribute__((aligned(16)));
    void *cm;
    void *g;
    char *s1;
    char *s2;
    char *user;
    int unset;

    L.junk[0] = unset;
    cm = get_main_cameraman();
    if (cm != 0) {
        get_camera_parameter_cameraman(L.p60, L.p70, L.p80, L.pA0, cm);
        s2 = 0;
        s1 = 0;
        for (g = isysGroupForFirst(get_camera_target_group(cm), 0); g != 0; g = isysGroupForNext(g, 0)) {
            s1 = *(char **)g;
            if (GAMEUTIL_is_player_obj(s1) == 1) {
                s2 = s1;
                break;
            }
        }
        if (s1 != 0)
            isysGroupForExit(s1, 0);
        if (s2 != 0) {
            *(s128 *)L.p90 = **(s128 **)(GetLayoutClass(s2) + 0x134);
            L.name[0] = 0;
            getStageAreaName(L.name, L.p60);
            out[0] = 0;
            user = username();
            iosGetClock(L.clk);
            iosSPrintf(B_00183B20, "%02x%02x", L.clk[6], L.clk[5]);
            iosSPrintf(out, "%s_%s_%s_%s %.1f %.1f %.1f %.2f %.2f %.2f %.1f %.1f %.1f", user, B_00183B20, L.name, tag,
                       L.p60[0], L.p60[1], L.p60[2], L.p70[0], L.p70[1], L.p70[2], L.p90[0], L.p90[1], L.p90[2]);
            return 1;
        }
    }
    return 0;
}
