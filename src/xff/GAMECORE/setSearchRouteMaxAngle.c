extern float iosGetCosf(float);

void setSearchRouteMaxAngle(void *work, float angle)
{
    if (angle == 3.1415926f) {
        *(float *)((char *)work + 0x3B4) = -1.0f;
    } else {
        *(float *)((char *)work + 0x3B4) = iosGetCosf(angle);
    }
}
