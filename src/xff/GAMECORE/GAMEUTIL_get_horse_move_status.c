extern char *GetCharacterClass(void *);

static inline int get_character_type(void *actor)
{
    char *c;
    if (actor != 0) {
        c = GetCharacterClass(actor);
        if (c != 0)
            return *(short *)(c + 0x370);
    }
    return -1000000;
}

static inline int is_horse_obj(void *actor)
{
    return get_character_type(actor) == 3;
}

extern int ControlMode_HORSE_WALK;
extern int ControlMode_HORSE_TURN_WALK;
extern int ControlMode_HORSE_RUN_N;
extern int ControlMode_HORSE_TURN_RUN_N;
extern int ControlMode_HORSE_RUN;
extern int ControlMode_HORSE_TURN_RUN;

int GAMEUTIL_get_horse_move_status(int *out, void *actor)
{
    int mode = 0;
    int moving = 0;

    if (is_horse_obj(actor)) {
        int m = *(int *)(GetCharacterClass(actor) + 0x750);

        if (m == ControlMode_HORSE_WALK || m == ControlMode_HORSE_TURN_WALK) {
            mode = 2;
            moving = 1;
        } else if (m == ControlMode_HORSE_RUN_N || m == ControlMode_HORSE_TURN_RUN_N) {
            mode = 3;
            moving = 1;
        } else if (m == ControlMode_HORSE_RUN || m == ControlMode_HORSE_TURN_RUN) {
            mode = 4;
            moving = 1;
        } else {
            mode = 1;
        }
    }
    if (out != 0)
        *out = mode;
    return moving;
}
