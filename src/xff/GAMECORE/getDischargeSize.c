extern char *getEditWorkInitData(int);

int getDischargeSize(char *o)
{
    char *d = getEditWorkInitData(*(int *)(o + 8));
    float min = 32.0f;

    return *(float *)(d + 0x10) * 112.0f + min;
}
