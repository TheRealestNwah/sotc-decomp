extern float iosGetCosf(float);

void setRouteMinAngle(void *work, float angle)
{
    *(float *)((char *)work + 0x3B0) = iosGetCosf(angle);
}
