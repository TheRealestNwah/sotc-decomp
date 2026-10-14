extern char gcGlobalVar[];

int checkFadeParam(float *p)
{
    if (*(float *)(gcGlobalVar + 0x168) <= p[1]) {
        return 1;
    }
    return 0;
}
