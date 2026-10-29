typedef struct { int a; int b; int c; int d; int e; } CameraEtcFlags;
extern int is_pass_camera_etc_condition(unsigned int, CameraEtcFlags *);
int is_hit_leave_plane_game_camera(char *camera, int b, int c, int d)
{
    return is_pass_camera_etc_condition(3, (CameraEtcFlags *)(camera + 16));
}
