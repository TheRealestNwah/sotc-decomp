#ifndef GAMECORE_CAMERA_TARGET_APPROACH_H
#define GAMECORE_CAMERA_TARGET_APPROACH_H

/* GAMECORE camera target approach
 * (src/xff/GAMECORE/camera_target_approach.c). ApproachWork is a padded view
 * of the work doit_camera_target_approach takes; the file's other struct
 * views stay local, since only the group's own functions use them. */

typedef struct {
    char pad0[0x10];
    char filter[0x30];
    float yaw;
    char aim[1];
} ApproachWork;

void doit_camera_target_approach(ApproachWork *w, char **cam, void *game, void *arg, float rate);
void constructor_camera_target_approach(char *p);
float get_upper_limit_clip_default_pitch_camera_target_approach(int *status, float fparg0);
int is_cut_default_pitch_interp_camera_target_approach(int *arg0);
void reset_pitch_rot_cntrl_camera_target_approach(char *control);
float act_pitch_rot_camera_target_approach(char *c, float pitch, float aim, float dt);
void act_approach_judge_ray_check_camera_target_approach(void *a0, float *pos, float *look, char *st, char *cam, int t1);
int get_status_camera_target_approach(char *work);

#endif /* GAMECORE_CAMERA_TARGET_APPROACH_H */
