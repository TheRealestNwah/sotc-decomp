extern float iosGetCosf(float);

void setReductionCosUserPathWork(void *work, float angle)
{
    if (angle == 3.1415926f) {
        *(float *)((char *)work + 0x3C8) = -1.0f;
    } else {
        *(float *)((char *)work + 0x3C8) = iosGetCosf(angle);
    }
}
