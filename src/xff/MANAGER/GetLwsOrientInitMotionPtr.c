extern int getAnimObjResource();

int GetLwsOrientInitMotionPtr(char *p, int a)
{
    return getAnimObjResource(*(char **)(p + 0x7C) + 0x50, a);
}
