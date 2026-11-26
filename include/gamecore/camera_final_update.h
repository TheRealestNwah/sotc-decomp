#ifndef GAMECORE_CAMERA_FINAL_UPDATE_H
#define GAMECORE_CAMERA_FINAL_UPDATE_H

/* GAMECORE camera final update (src/xff/GAMECORE/camera_final_update.c). Its
 * struct views (Blend, CamPos and the vector unions) stay local, since only
 * the group's own functions use them. */

void doit_camera_final_update(char *mgr, char *cam, char *mode, char *arg3, float dt);
void constructor_camera_final_update(char *c);

#endif /* GAMECORE_CAMERA_FINAL_UPDATE_H */
