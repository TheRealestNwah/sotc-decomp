typedef struct {
    int pad0;
    float x;
    float y;
    int type;
    float z;
    int time;
    char pad18[0x18];
} ExpressionParam;

extern char *nico_playerGetExpressionChange(void *);
extern void constructor_expression_change(char *);
extern void func_00081FF0(ExpressionParam *, int);
extern void add_element_expression_change(char *, int, int, int, float, float, float);
extern int is_doing_nico_sight_on(void *);
extern float get_object_local_base_yaw_nico_sight_on(void *);
extern float *doit_expression_change(char *, int, float, void *);

static float func_0008F220(void *player, int kind, void *obj)
{
    ExpressionParam param;
    char *change = nico_playerGetExpressionChange(player);
    float yaw = 0;
    float *r;

    constructor_expression_change(change);
    if (kind >= 3) {
        if (kind < 13)
            goto add;
        if (kind < 24) {
            if (kind >= 14) {
            add:
                func_00081FF0(&param, kind);
                add_element_expression_change(change, kind, param.type, param.time, param.x * 0.0174532925f,
                                              param.y * 0.0174532925f, param.z * 0.0174532925f);
            }
        }
    }
    if (is_doing_nico_sight_on(obj) == 1)
        yaw = get_object_local_base_yaw_nico_sight_on(obj);
    r = doit_expression_change(change, kind, yaw, player);
    return r ? r[1] : 0;
}
