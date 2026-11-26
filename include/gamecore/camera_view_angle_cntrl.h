#ifndef GAMECORE_CAMERA_VIEW_ANGLE_CNTRL_H
#define GAMECORE_CAMERA_VIEW_ANGLE_CNTRL_H

/* GAMECORE camera view angle control
 * (src/xff/GAMECORE/camera_view_angle_cntrl.c). Its struct view (DispWork)
 * stays local, since only the group's own static functions use it. */

void doit_camera_view_angle_cntrl(char *cntrl, char *cam, int flag, float dt);
void constructor_camera_view_angle_cntrl(char *c);
float get_view_angle_camera_view_angle_cntrl(void *arg0);

#endif /* GAMECORE_CAMERA_VIEW_ANGLE_CNTRL_H */
