extern float D_00139F54;
extern float D_00139F58;

float get_aspect_ratio(void *arg0)
{
    return ((*(float *)((char *)(arg0) + 8)) * D_00139F54) / D_00139F58;
}
