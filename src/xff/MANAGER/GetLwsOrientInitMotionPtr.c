extern int getAnimObjResource(unsigned int *);

int GetLwsOrientInitMotionPtr(char *p, int a)
{
    return getAnimObjResource((unsigned int *)(*(char **)(p + 0x7C) + 0x50));
}
