extern float calcAngleTime(float angle, float a, float b, float c);

float calcTurnTime2(char *obj, float angle)
{
    return calcAngleTime(angle, *(float *)(obj + 0xA8), *(float *)(obj + 0xA4),
                         *(float *)(**(char ***)(obj + 0x1C) + 0x78));
}
