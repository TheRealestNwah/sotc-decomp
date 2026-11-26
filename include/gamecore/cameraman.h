#ifndef GAMECORE_CAMERAMAN_H
#define GAMECORE_CAMERAMAN_H

/* GAMECORE cameraman (src/xff/GAMECORE/cameraman.c). Cameraman is a padded
 * view: only the fields the group reads are named. */

typedef struct {
    int camObj;
    int mode;
    int owner;
    char pad0C[0xC];
    int prevTarget;
    int target;
    char pad20[0x37C0 - 0x20];
    float timer;
} Cameraman;

void doit_cameraman(Cameraman *c, float f);
void *get_camera_obj(void *manager);
void set_camera_mode(void *arg0, int arg1);
int get_cur_camera_mode(void *arg0);
char *get_camera_mode_name(int mode);
int get_camera_target_group(void *arg0);
int get_camera_move_collision_group(void *arg0);
int get_camera_visible_collision_group(void *arg0);
int get_player_collision_group_cameraman(void *arg0);
int get_lws_animation_collision_group_cameraman(void *arg0);
char *get_game_camera(void *object);
int get_cur_camera_target(void *arg0);
int get_game_camera_WV_matrix(int arg0);
int is_game_camera_mode_now(void *arg0);
int is_camera_target_change(void *arg0);
int is_camera_target_debug_move(void);
int change_camera_target(void *arg0, int arg1);
int change_to_player_camera_target(int *p);
void set_camera_parameter_cameraman(void **manager, void *position, void *direction, void *up, float angle);
void set_camera_parameter_and_update_cameraman(void **manager, void *position, void *direction, void *up, float angle);
void check_free_cameraman(void **slot);

#endif /* GAMECORE_CAMERAMAN_H */
