typedef struct {
    float f0;
    float f4;
    float f8;
    int left;
    float f10;
    int right;
    float f18;
    float f1C;
    float f20;
    float f24;
} ExprParam;

typedef struct { char pad[0x180]; float dt; } GcGlobal;
extern GcGlobal gcGlobalVar;
extern int GAMEUTIL_is_player_obj(void *);
extern void *nico_playerGetSightOn(void *);
extern char *GetCharacterClass(void *);
extern void *nico_playerGetExpression(void *);
extern void update_type_expression(void *, int, float);
extern void func_00081FF0(ExprParam *, int);
extern int is_doing_nico_sight_on(void *);
extern float get_object_local_merge_yaw_nico_sight_on(void *);
extern float get_merge_pitch_nico_sight_on(void *);
extern float func_0008F220(void *, int, void *);
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern int func_0008F328(int);
extern float GAMEUTIL_get_cur_interp_ratio_expression(void *);
extern int get_pre_type_expression(void *);
extern void func_000827C8(void *, float, float, float, float);
extern void func_000841C0(void *, float, float, float, float);
extern void func_000860A0(void *, float, float, float, float);
extern void func_000886D0(void *, float, float, float, float);
extern void func_0008B410(void *, float, float, float, float);
extern void func_0008F378(void *, float, float, float, float);
extern void func_0008F560(void *, float, float, float, float);
extern void func_0008F748(void *, float, float, float, float);
extern void func_0008F930(void *, float, float, float, float);
extern void func_0008FB18(void *, float, float, float, float);
extern void func_0008D008(void *, float, float, float, float);
extern void func_0008DF68(void *, float, float, float, float);
extern void func_0008F360(void *, float, float, float, float);
extern void doit_expression(void *, float, float);

void nico_playerExpression(void *obj)
{
    ExprParam p;
    void *sight;
    char *cc;
    int kind;
    void *expr;
    float yaw, pitch, ky, kp;
    int type;

    if (GAMEUTIL_is_player_obj(obj) != 1)
        return;
    sight = nico_playerGetSightOn(obj);
    cc = GetCharacterClass(obj);
    if (*(char **)(cc + 0x578) != 0)
        kind = (*(unsigned int *)(*(char **)(cc + 0x578) + 0x6C) >> 10) & 0x1F;
    else
        kind = 1;
    expr = nico_playerGetExpression(obj);
    update_type_expression(expr, kind, gcGlobalVar.dt);
    pitch = 0.0f;
    yaw = pitch;
    func_00081FF0(&p, kind);
    kp = pitch;
    if (is_doing_nico_sight_on(sight) == 1) {
        yaw = get_object_local_merge_yaw_nico_sight_on(sight);
        pitch = get_merge_pitch_nico_sight_on(sight);
    }
    yaw = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(func_0008F220(obj, kind, sight), yaw);
    if (kp <= yaw)
        ky = p.f18;
    else
        ky = p.f1C;
    if (pitch >= 0.0f)
        kp = p.f20;
    else
        kp = p.f24;
    pitch *= kp;
    yaw *= -ky;
    type = kind;
    if (func_0008F328(type) == 1) {
        pitch = 0.0f;
        yaw = pitch;
        if (GAMEUTIL_get_cur_interp_ratio_expression(expr) < 1.0f)
            type = get_pre_type_expression(expr);
    }
    if (func_0008F328(type) == 0) {
        switch (type) {
        case 2: func_000827C8(expr, yaw, pitch, ky, kp); break;
        case 3: func_000841C0(expr, yaw, pitch, ky, kp); break;
        case 5: func_000860A0(expr, yaw, pitch, ky, kp); break;
        case 7: func_000886D0(expr, yaw, pitch, ky, kp); break;
        case 9: case 11: func_0008B410(expr, yaw, pitch, ky, kp); break;
        case 13: func_0008F378(expr, yaw, pitch, ky, kp); break;
        case 14: func_0008F560(expr, yaw, pitch, ky, kp); break;
        case 16: func_0008F748(expr, yaw, pitch, ky, kp); break;
        case 18: func_0008F930(expr, yaw, pitch, ky, kp); break;
        case 20: case 22: func_0008FB18(expr, yaw, pitch, ky, kp); break;
        case 24: func_0008D008(expr, yaw, pitch, ky, kp); break;
        case 25: func_0008DF68(expr, yaw, pitch, ky, kp); break;
        case 26: func_0008F360(expr, yaw, pitch, ky, kp); break;
        }
    }
    doit_expression(expr, p.f0, gcGlobalVar.dt);
}
