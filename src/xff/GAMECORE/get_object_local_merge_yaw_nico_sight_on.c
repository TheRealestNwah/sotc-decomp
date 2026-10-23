extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);
extern void GAMEUTIL_get_local_directionZ(float *, void *);
extern void GAMEUTIL_get_yaw_pitch_by_direction(float *, float *, float *);
extern float GAMEUTIL_increase_yaw(int, float, float);

typedef struct {
    int pad;
    /* The char member lets the local float stores alias this load, so it
       stays after them, as in the original. */
    union {
        void *obj;
        char alias;
    } obj;
    char pad8[0x240];
    float merge;
    char pad24C[0x34];
    float yaw;
} Nico;

float get_object_local_merge_yaw_nico_sight_on(Nico *nico)
{
    float dir[4];
    float yaw;
    float pitch;

    yaw = 0.0f;
    pitch = 0.0f;
    GAMEUTIL_get_local_directionZ(dir, nico->obj.obj);
    GAMEUTIL_get_yaw_pitch_by_direction(&yaw, &pitch, dir);
    return GAMEUTIL_increase_yaw(0, GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(yaw, nico->yaw), nico->merge);
}
