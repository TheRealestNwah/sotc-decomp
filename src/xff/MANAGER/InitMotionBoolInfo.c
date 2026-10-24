typedef struct {
    signed char b0;
    signed char b1;
    signed char b2;
} MotionBoolInfo;

extern MotionBoolInfo D_001365C0;

void InitMotionBoolInfo(MotionBoolInfo *info)
{
    *info = D_001365C0;
}
