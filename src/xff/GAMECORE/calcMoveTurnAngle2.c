extern float RO_001813E8;
extern float calcMoveAngle(int, float, float, float, float);
float calcMoveTurnAngle2(char *p, float a)
{
    return calcMoveAngle(0, a, *(float *)(p + 0xA8), *(float *)(**(char ***)(p + 0x1C) + 0x78), RO_001813E8);
}
