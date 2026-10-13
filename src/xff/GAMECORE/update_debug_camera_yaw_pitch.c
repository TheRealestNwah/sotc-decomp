extern void GAMEUTIL_get_yaw_pitch_by_direction(void *, void *, int);
extern unsigned char D_0017B690[1];
extern unsigned char D_0017B694[1];

void update_debug_camera_yaw_pitch(int arg0)
{
    GAMEUTIL_get_yaw_pitch_by_direction(&D_0017B690, &D_0017B694, arg0);
}
