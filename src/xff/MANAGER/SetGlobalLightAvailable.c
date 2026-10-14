void SetGlobalLightAvailable(char *p, int a)
{
    if (p != 0) {
        *(int *)(p + 0x144) = a;
    }
}
