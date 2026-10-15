char *GetNextWorkLightClass(char *c)
{
    char *r = 0;
    int n = *(int *)(c + 0x530);
    if (n < 3) {
        r = c + n * 64 + 0x450;
        ((int *)(c + 0x534))[n] = (int)r;
        *(int *)(c + 0x530) += 1;
    }
    return r;
}
