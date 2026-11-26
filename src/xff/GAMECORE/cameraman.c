/* The union store keeps the dt load after the prevTarget store (strict aliasing would hoist it); the pins give the Original's registers. */
#include "common.h"
#include "gamecore/cameraman.h"
typedef struct { char pad[0x170]; float dt; }
GcGlobal;
extern GcGlobal gcGlobalVar;
extern int DebugFindPlayer(int);
extern int GAMEUTIL_get_first_obj(int);
extern void SetSeamlessStageControlObject(int);
extern void update_camera_obj(int);
typedef union { int i; float f; } IF;
extern char RO_001810A8[];
extern char RO_001810C8[];
extern char RO_001810E8[];
extern char RO_00181108[];
extern char RO_00181130[];
extern char RO_00181158[];
extern char RO_00181188[];
extern char RO_001811A8[];
extern void *get_clip_screen(void *);
extern void set_camera_position(void *, void *);
extern void set_camera_direction(void *, void *);
extern void set_camera_up_direction(void *, void *);
extern void set_view_angle(void *, float);
typedef int Qword __attribute__((mode(TI)));
typedef union Vector { Qword quad; float v[4]; } Vector;
typedef struct ClipScreen ClipScreen;
extern int get_camera_position(int);
extern int get_camera_direction(int);
extern int get_camera_up_direction(int);
extern float get_view_angle(ClipScreen *);
extern void isysRequestDeleteObj(int);
extern void flush_game_camera(void *);
extern void iosFree(void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern void doit_game_camera(void *, void *, float);

static int func_000E32B0(char *p);
static void func_000E3348(void);
static void func_000E3350(void);
static void func_000E3358(void **o, float f);
static void func_000E33D0(void *p);

void doit_cameraman(Cameraman *c, float f)
{
    int *mode = &c->mode;

    {
        register GcGlobal *g asm("$5") = &gcGlobalVar;
        register int t asm("$3") = c->target;
        register float tm asm("$f0") = c->timer;
        ((IF *)&c->prevTarget)->i = t;
        c->timer = tm - g->dt;
    }
    ((void (*)(void *))func_000E3350)(c);
    if (((int (*)(void *))func_000E32B0)(c) == 0) {
        c->target = DebugFindPlayer(c->owner);
        if (c->target == 0) {
            c->target = GAMEUTIL_get_first_obj(c->owner);
            if (c->target == 0 && *mode != 2) {
                return;
            }
        }
    }
    ((void (*)(void *))func_000E3348)(c);
    SetSeamlessStageControlObject(c->target);
    ((void (*)(void *, float))func_000E3358)(c, f);
    update_camera_obj(c->camObj);
    func_000E33D0(c);
}

void *get_camera_obj(void *manager)
{
    return *(void **)manager;
}

void set_camera_mode(void *arg0, int arg1)
{
    (*(int *)((char *)(arg0) + 4)) = arg1;
}

int get_cur_camera_mode(void *arg0)
{
    return (*(int *)((char *)(arg0) + 4));
}

char *get_camera_mode_name(int mode)
{
    if (mode == 0)
        return RO_001810A8;
    if (mode == 1)
        return RO_001810C8;
    if (mode == 2)
        return RO_001810E8;
    if (mode == 3)
        return RO_00181108;
    if (mode == 4)
        return RO_00181130;
    if (mode == 5)
        return RO_00181158;
    if (mode == 6)
        return RO_00181188;
    return RO_001811A8;
}

int get_camera_target_group(void *arg0)
{
    return (*(int *)((char *)(arg0) + 8));
}

int get_camera_move_collision_group(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0xC));
}

int get_camera_visible_collision_group(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x10));
}

int get_player_collision_group_cameraman(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x14));
}

int get_lws_animation_collision_group_cameraman(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x14));
}

char *get_game_camera(void *object)
{
    return (char *)object + 0x20;
}

int get_cur_camera_target(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x1C));
}

int get_game_camera_WV_matrix(int arg0)
{
    return arg0 + 0x37D0;
}

int is_game_camera_mode_now(void *arg0)
{
    return (unsigned int) (*(unsigned int *)((char *)(arg0) + 4)) < 2U;
}

int is_camera_target_change(void *arg0)
{
    return (*(int *)((char *)(arg0) + 0x1C)) != (*(int *)((char *)(arg0) + 0x18));
}

int is_camera_target_debug_move(void)
{
    return 0;
}

int change_camera_target(void *arg0, int arg1)
{
    if (arg1 != 0) {
        (*(int *)((char *)(arg0) + 0x1C)) = arg1;
        return 1;
    }
    return 0;
}

int change_to_player_camera_target(int *p)
{
    void *pl = DebugFindPlayer(p[2]);
    if (pl == 0)
        return 0;
    p[7] = (int)pl;
    return 1;
}

void set_camera_parameter_cameraman(void **manager, void *position, void *direction, void *up, float angle)
{
    set_camera_position(*manager, position);
    set_camera_direction(*manager, direction);
    set_camera_up_direction(*manager, up);
    set_view_angle(get_clip_screen(*manager), angle);
}

void set_camera_parameter_and_update_cameraman(void **manager, void *position, void *direction, void *up, float angle)
{
    set_camera_position(*manager, position);
    set_camera_direction(*manager, direction);
    set_camera_up_direction(*manager, up);
    set_view_angle(get_clip_screen(*manager), angle);
    ((void (*)(void *))update_camera_obj)(*manager);
}

void get_camera_parameter_cameraman(Vector *position, Vector *direction, Vector *up,
                                    float *angle, void **manager)
{
    position->quad = ((Vector *)get_camera_position((int)*manager))->quad;
    direction->quad = ((Vector *)get_camera_direction((int)*manager))->quad;
    up->quad = ((Vector *)get_camera_up_direction((int)*manager))->quad;
    *angle = get_view_angle(get_clip_screen(*manager));
}

void check_free_cameraman(void **slot)
{
    void *camera=*slot;
    if (camera != 0) {
  isysRequestDeleteObj(*(int *)camera);
  flush_game_camera((char *)*slot + 0x20);
  iosFree(*slot);
  *slot=0;
    }
}

static int func_000E32B0(char *p)
{
    int found = 0;

    if (*(void **)(p + 0x1C) != 0) {
        void **it;
        void *obj = 0;

        for (it = isysGroupForFirst(*(void **)(p + 0x8), 0); it != 0; it = isysGroupForNext(it, 0)) {
            obj = *it;
            if (*(void **)(p + 0x1C) == obj) {
                found = 1;
                break;
            }
        }
        if (obj != 0)
            isysGroupForExit(obj, 0);
    }
    return found;
}

static void func_000E3348(void) {}

static void func_000E3350(void) {}

static void func_000E3358(void **o, float f)
{
    void *cam = *o;
    s128 v[3];

    v[0] = *((s128 * (*)(void *))get_camera_position)(cam);
    v[1] = *((s128 * (*)(void *))get_camera_direction)(cam);
    v[2] = *((s128 * (*)(void *))get_camera_up_direction)(cam);
    doit_game_camera(o + 8, o, f);
}

static void func_000E33D0(void *p) {}
