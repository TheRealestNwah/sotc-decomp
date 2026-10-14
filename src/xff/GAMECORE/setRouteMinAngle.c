extern float iosGetCosf();

void setRouteMinAngle(void *arg0)
{
    (*(float *)((char *)(arg0) + 0x3B0)) = iosGetCosf();
}
