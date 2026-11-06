
typedef int s128 __attribute__((mode(TI)));
extern s128 ZeroPoint;
extern s128 ZeroVector;
extern int GAMEUTIL_get_boss_interest_position(void *, int);
extern void constructor_double_spring_interp_cntrl3D(char *, float, float);
extern void func_000ED110(char *, void *, int, void *);
extern void CAM_init_aim_angle_rot(char *, int);
extern void CAM_init_camera_warp_cntrl(char *, int, int, int);
static void func_000EC8C8(char *self, char *c)
{
  float v[4];
  s128 buf;
  s128 *pb = &buf;
  char *a = c + 0x10;
  char *b = c + 0x90;
  int boss = GAMEUTIL_get_boss_interest_position(pb, 1);
  float *src = *((float **) c);
  v[0] = src[4];
  v[1] = src[5];
  v[2] = src[6];
  v[3] = src[7];
  src = (int *) a;
  *src = 0;
  *((s128 *) (a + 0x10)) = ZeroPoint;
  constructor_double_spring_interp_cntrl3D(c + 0x30, 0.001f, 1.0f);
  *((int *) (a + 0x60)) = 0;
  *((s128 *) (a + 0x70)) = ZeroVector;
  func_000ED110(a, v, boss, pb);
  CAM_init_aim_angle_rot(b, 0);
  CAM_init_aim_angle_rot(c + 0xD4, 1);
  *((int *) (b + 0x88)) = 0;
  *((int *) (b + 0x8C)) = 0;
  CAM_init_camera_warp_cntrl(self + 0x1840, 2, 3, 0);
}
