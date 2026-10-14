typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } CameraWord;
void copy_mode_common_camera_data(CameraWord *d, CameraWord *s)
{
 d[0].q = s[0].q;
 d[1].q = s[1].q;
 d[2].q = s[2].q;
 d[3].f[0] = s[3].f[0];
 d[3].f[1] = s[3].f[1];
 d[3].f[2] = s[3].f[2];
}
