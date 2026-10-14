void setWormIKBoundDynamics(char *p, float f1, float f2, float f3)
{
    *(float *)(p + 0x1280) = f1;
    *(float *)(p + 0x1284) = f2;
    *(float *)(p + 0x1288) = f3;
}
