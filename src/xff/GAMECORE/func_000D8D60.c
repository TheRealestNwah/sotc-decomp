typedef int s128 __attribute__((mode(TI)));
typedef union { s128 q; float f[4]; } Vec4;

extern Vec4 ZeroVector;
extern float GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(float, float);

static void func_000D8D60(Vec4 *out, float *dir)
{
    out->q = ZeroVector.q;
    out->f[0] = dir[12];
    out->f[1] = -1.5707963f;
    out->f[2] = GAMEUTIL_get_move_radi_from_yaw1_to_yaw2(3.1415926f, dir[12]);
}
