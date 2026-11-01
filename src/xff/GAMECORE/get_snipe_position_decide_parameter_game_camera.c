extern int CAM_get_target_obj(void *);
extern int GAMEUTIL_get_player_obj(void);
extern void GAMEUTIL_get_camera_target_look_at_position(float *, int);

typedef union { float f; int i; } FU;

#define ABS(x) ((x) < 0.0f ? -(x) : (x))

void get_snipe_position_decide_parameter_game_camera(float *pos, FU *param, char *cam)
{
    char *c = cam + 0x700;
    int obj = CAM_get_target_obj(cam + 0x15AC);

    if (obj == 0)
        obj = GAMEUTIL_get_player_obj();
    GAMEUTIL_get_camera_target_look_at_position(pos, obj);
    param[0].f = *(float *)(c + 0x54);
    param[1].f = *(float *)(c + 0x5C);
    if (*(int *)(cam + 0x24E4) == 1) {
        if (*(float *)(c + 0x44) >= 0.0f && *(float *)(c + 0x44) < ABS(param[0].f)) {
            if (param[0].f >= 0.0f)
                param[0].f = *(float *)(c + 0x44);
            else
                param[0].f = -*(float *)(c + 0x44);
        }
        if (*(float *)(c + 0x48) >= 0.0f && *(float *)(c + 0x48) < ABS(param[1].f)) {
            if (param[1].f >= 0.0f)
                param[1].f = *(float *)(c + 0x48);
            else
                param[1].f = -*(float *)(c + 0x48);
        }
    }
    param[2].f = -*(float *)(cam + 0x1408);
    param[3].i = 0;
}
