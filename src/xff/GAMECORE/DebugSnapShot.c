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


typedef struct { char pad0[0x168]; float time; } GcGlobalVarT;
extern GcGlobalVarT gcGlobalVar;
typedef struct {
    int f0;
    int f4;
    int f8;
    char padC[0xF98 - 0xC];
    int trig;
    int f9C;
    int fA0;
} PadMgrT;
extern PadMgrT padManagerData;
extern float D_00179920;
extern int D_0017991C;
extern int D_00179910;
extern int D_00179908;
extern int D_0017990C;
extern int D_00179918;
extern int D_001798CC;
extern float D_00179914;
extern char *getDemoCutName(void);
extern void SnapShotDebug(char *, int, int, int, int);
extern void SnapShotHigh(int, int, int, int);
extern int *getDebugCameraBlurSw(void);
extern int get_cur_camera_mode(void *);
extern void scrRunM(int);
extern void scrRun(void);
extern void set_debug_camera_move_diff(float, float);
extern void SetCameraResetSw(int);

void DebugSnapShot(void)
{
    char buf[0x100];
    unsigned long clk; /* clock bytes; an 8-byte scalar keeps the 16-byte frame slot shared with blur's spill */
    int blur;
    char *user;
    int i;
    int mode;
    int sel;
    /* Nested in the Original: callers pass the static chain in $v0, and the
       nested function saves it in its frame. The asm name keeps gcc's ".0"
       suffix off so the splice step can place it. */
    auto int func_00004868(char *out, char *tag) __asm__("func_00004868");

    int func_00004868(char *out, char *tag)
    {
        struct {
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

    if (0.0f < D_00179920 && 0.29999998211860657f <= gcGlobalVar.time - D_00179920) {
        D_00179920 = 0.0f;
        return;
    }
    if (padManagerData.f8 & 0x400) {
        if (!(0.0f < D_00179920)) {
            D_00179920 = gcGlobalVar.time;
            return;
        }
        if (gcGlobalVar.time - D_00179920 < 0.29999998211860657f) {
            if (getDemoCutName() != 0) {
                user = username();
                iosGetClock((unsigned char *)&clk);
                iosSPrintf(B_00183B20, "%02x%02x", ((unsigned char *)&clk)[6], ((unsigned char *)&clk)[5]);
                iosSPrintf(buf, "%s_%s_demo %s", user, B_00183B20, getDemoCutName());
                SnapShotDebug(buf, 0x200, 0x180, 0x5A, 3);
            } else if (func_00004868(buf, "") != 0) {
                sel = D_001798CC >= 1;
                if (padManagerData.f0 & 8)
                    sel = D_001798CC < 1;
                if (sel) {
                    func_00004868(buf, "col");
                    SnapShotDebug(buf, 0x200, 0x180, 0x5A, 2);
                } else {
                    func_00004868(buf, "stg");
                    SnapShotDebug(buf, 0x200, 0x180, 0x5A, 1);
                }
            }
        }
        D_00179920 = 0.0f;
        return;
    }
    if (padManagerData.fA0 & 0x400) {
        if (padManagerData.trig & 2) {
            if (func_00004868(buf, "local") != 0)
                SnapShotDebug(buf, D_0017991C, D_0017991C * 3 / 4, 0x46, 0);
            return;
        }
        if (D_00179910 >= 2) {
            mode = 0;
            blur = *getDebugCameraBlurSw();
            if (get_cur_camera_mode(get_main_cameraman()) == 6)
                mode = 0x10E;
            scrRunM(10);
            set_debug_camera_move_diff(D_00179914 * 0.017453292f, 0.0f);
            scrRunM(2);
            *getDebugCameraBlurSw() = 0;
            for (i = 0; i < D_00179910 && (padManagerData.trig & 0x900) != 0x900;) {
                i++;
                SetCameraResetSw(1);
                SnapShotHigh(1 << D_00179908, D_0017990C, mode, D_00179918);
                scrRun();
            }
            set_debug_camera_move_diff(0.0f, 0.0f);
            *getDebugCameraBlurSw() = blur;
        } else {
            SnapShotHigh(1 << D_00179908, D_0017990C, 0, D_00179918);
        }
    }
}
