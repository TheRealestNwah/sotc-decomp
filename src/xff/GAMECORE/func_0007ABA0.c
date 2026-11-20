typedef int s128 __attribute__((mode(TI)));
extern void *get_main_cameraman(void);
extern void *get_game_camera(void *);
extern int get_boss_interest_position_game_camera(void *, void *);
extern int *ScriptCtrlDef_SCRPlayerWhistle;
extern void CharaCtrlSetOutsideScriptCtrlStatus(void *, int);
extern char *GAMEUTIL_get_motion_kind(void *);
extern int get_object_interest_mode_target_game_camera(void *);
extern int GAMEUTIL_get_boss_interest_position(void *, int);
extern int get_game_camera_cur_mode(void *);
extern void *GAMEUTIL_get_horse_obj(void);
extern char *GetLayoutClass(void *);

static inline unsigned int motionAttr(void *obj)
{
    char *m = GAMEUTIL_get_motion_kind(obj);

    return m != 0 ? (*(unsigned int *)(m + 0x6C) >> 15) & 7 : 0;
}

static int func_0007ABA0(s128 *out, char *w, void *obj)
{
    void *cam = get_game_camera(get_main_cameraman());
    void *horse;

    if (get_boss_interest_position_game_camera(out, cam) == 1) {
        CharaCtrlSetOutsideScriptCtrlStatus(obj, ScriptCtrlDef_SCRPlayerWhistle[1]);
        return 1;
    }
    if (*(int *)(w + 0x4B0) == 1 || (motionAttr(obj) == 2 && get_object_interest_mode_target_game_camera(cam) == 1)) {
        if (GAMEUTIL_get_boss_interest_position(out, 1) == 1)
            return 1;
    }
    if (get_game_camera_cur_mode(cam) == 5 || (motionAttr(obj) == 2 && get_object_interest_mode_target_game_camera(cam) == 0)) {
        horse = GAMEUTIL_get_horse_obj();
        if (horse != 0) {
            *out = **(s128 **)(GetLayoutClass(horse) + 0x134);
            return 1;
        }
    }
    return 0;
}
