#ifndef GAMECORE_CAMERAMAN_MANAGER_H
#define GAMECORE_CAMERAMAN_MANAGER_H

/* GAMECORE camera manager (src/xff/GAMECORE/cameraman_manager.c): picks the
 * main cameraman. Structs are padded views: only the fields the group reads
 * are named. */

typedef struct {
    int selected;
    int total;
    int cameras[5];
} CameraManager;

void doit_cameraman_manager(float time);
int get_main_cameraman(void);
void *get_main_cameraman_camera_obj(void);

#endif /* GAMECORE_CAMERAMAN_MANAGER_H */
