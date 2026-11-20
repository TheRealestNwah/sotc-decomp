extern void *get_main_cameraman(void);
extern int get_cur_camera_target(void *);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void iosInitKPrintfContext(void *, float, float, float, float, float, float, int, int);
extern void iosSetKPrintfColorContext(void *, float, float, float, float, int);
extern void iosSetKPrintfLocateContext(void *, float, float);
extern void kprintfContext(void *, const char *, ...);
extern int *gcGetStageData(int);
extern char *GetCharacterClass(int);
extern void DEBUG_get_2d_font_disp_position(float *, float *, float, float);
extern float DEBUG_get_2d_font_default_height_offset(void);
extern void DEBUG_disp_object_info(int, void *, float, float, float);
extern float DEBUG_disp_collision_name(int, void *, float, float, float);
extern int checkUser(const char *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void *, int);
extern void isysGroupForExit(void *, int);
extern void func_000032A0(void *, int, int, float, float);
extern void func_00007CC8(int, void *, float, float, float);
extern void *func_00004F78(void);
extern void func_00005138(int, void *);
typedef struct { char pad0[0x168]; float f168; char pad16C[0x14]; float f180; char pad184[0x134]; char group[0x54]; int stage; } GlobalVar;
extern GlobalVar gcGlobalVar;
extern int padManagerData[];
extern int D_001798B8;
extern int D_00179A50;
extern const char RO_0017C100[];
extern const char RO_0017C108[];
extern const char RO_0017C258[];
extern const char RO_0017C618[];
extern const char RO_0017C660[];
extern const char RO_0017C668[];
extern const char RO_0017C670[];
extern const char RO_0017C678[];
extern const char RO_0017C680[];

static void func_000052B0(void)
{
    char ctx[0x40];
    char ctx2[0x40];
    float px, py;
    int target;
    int user;
    void *sel;
    float one = 1.0f;

    target = get_cur_camera_target(get_main_cameraman());
    iosDlPushLayer(0x1D);
    iosInitKPrintfContext(ctx, -250.0f, -200.0f, one, one, one, one, 0, 0);
    if ((unsigned)(D_001798B8 - 1) < 2 && gcGlobalVar.stage != -1
        && gcGetStageData(gcGlobalVar.stage) != 0) {
        const char *title = RO_0017C660;
        int name = *gcGetStageData(gcGlobalVar.stage);
        iosSetKPrintfColorContext(ctx, one, one, one, one, 0);
        kprintfContext(ctx, RO_0017C100, title);
        iosSetKPrintfColorContext(ctx, 0.25f, 0.75f, one, one, 0);
        kprintfContext(ctx, RO_0017C108, name);
    } else {
        const char *s = RO_0017C618;
        iosSetKPrintfColorContext(ctx, one, one, one, one, 0);
        kprintfContext(ctx, RO_0017C100, s);
        iosSetKPrintfColorContext(ctx, 0.25f, 0.75f, one, one, 0);
        kprintfContext(ctx, RO_0017C108, s);
    }
    if (target != 0) {
        px = 0.0f;
        py = 0.0f;
        iosInitKPrintfContext(ctx2, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0, 1);
        switch (D_001798B8) {
        case 0:
            GetCharacterClass(target);
            break;
        case 1:
            DEBUG_get_2d_font_disp_position(&px, &py, 0.025f, 0.39f);
            iosSetKPrintfLocateContext(ctx2, px, py);
            func_000032A0(ctx2, target, 1, gcGlobalVar.f168, gcGlobalVar.f180);
            break;
        case 2:
            DEBUG_get_2d_font_disp_position(&px, &py, 0.025f, 0.39f);
            iosSetKPrintfLocateContext(ctx2, px, py);
            func_000032A0(ctx2, target, 0, gcGlobalVar.f168, gcGlobalVar.f180);
            break;
        case 3:
            iosSetKPrintfColorContext(ctx2, 0.6f, 1.0f, 0.6f, 1.0f, 0);
            DEBUG_get_2d_font_disp_position(&px, &py, 0.635f, 0.05f);
            func_00007CC8(target, ctx2, px, py, DEBUG_get_2d_font_default_height_offset());
            px = 69.12f;
            py = 13.44f;
            iosSetKPrintfColorContext(ctx2, 1.0f, 1.0f, 1.0f, 1.0f, 0);
            iosSetKPrintfLocateContext(ctx2, px, py);
            func_000032A0(ctx2, target, 10, gcGlobalVar.f168, gcGlobalVar.f180);
            break;
        case 4:
            iosSetKPrintfColorContext(ctx2, 0.6f, 1.0f, 0.6f, 1.0f, 0);
            DEBUG_get_2d_font_disp_position(&px, &py, 0.6f, 0.05f);
            DEBUG_disp_object_info(target, ctx2, px, py, DEBUG_get_2d_font_default_height_offset());
            break;
        case 5:
            iosSetKPrintfColorContext(ctx2, 0.6f, 1.0f, 0.6f, 1.0f, 0);
            DEBUG_get_2d_font_disp_position(&px, &py, 0.057f, 0.05f);
            DEBUG_disp_object_info(target, ctx2, px, py, DEBUG_get_2d_font_default_height_offset());
            DEBUG_get_2d_font_disp_position(&px, &py, 0.635f, 0.05f);
            func_00007CC8(target, ctx2, px, py, DEBUG_get_2d_font_default_height_offset());
            break;
        case 6:
            iosSetKPrintfColorContext(ctx2, 0.6f, 1.0f, 0.6f, 1.0f, 0);
            DEBUG_get_2d_font_disp_position(&px, &py, 0.635f, 0.05f);
            py = DEBUG_disp_collision_name(target, ctx2, px, py, DEBUG_get_2d_font_default_height_offset());
            break;
        default:
            __asm__ __volatile__("break 0");
        }
    }
    user = 0;
    iosSetKPrintfColorContext(ctx, 0.0f, 1.0f, 0.3f, 1.0f, 0);
    kprintfContext(ctx, RO_0017C258);
    if (checkUser(RO_0017C668) || checkUser(RO_0017C670) || checkUser(RO_0017C678) || checkUser(RO_0017C680))
        user = 1;
    if (user && (padManagerData[0] & 1) && (padManagerData[2] & 2)) {
        void **link;
        int obj = 0;
        D_00179A50 = (D_00179A50 + 1) % 3;
        for (link = isysGroupForFirst(gcGlobalVar.group, 0); link != 0; link = isysGroupForNext(link, 0)) {
            obj = *(int *)link;
            GetCharacterClass(obj)[0x2B4] = D_00179A50;
        }
        if (obj != 0)
            isysGroupForExit((void *)obj, 0);
    }
    if (padManagerData[0] & 2) {
        sel = func_00004F78();
        if ((padManagerData[2] & 1) && sel != 0)
            func_00005138(target, sel);
    }
    iosDlPopLayer();
}
