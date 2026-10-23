typedef struct { char pad[0xA8]; int enabled; } CameraSettings;
typedef struct { char pad[0xC]; int active; } ObstacleAvoid;
extern float GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(float, float);

int CAM_act_avoid_rot_obstacle_avoid_cntrl(char *camera, CameraSettings **context)
{
    ObstacleAvoid *avoid = (ObstacleAvoid *)(camera + 0x174C);
    int result;
    if ((*context)->enabled == 0 || avoid->active == 0) {
        result = 0;
    } else {
        float delta = GAMEUTIL_get_move_radi_from_pitch1_to_pitch2(*(float *)(camera + 0xF34), *(float *)(camera + 0xD4));
        result = 0;
        if (!(delta <= 0.0f))
            result = 1;
    }
    return result;
}
