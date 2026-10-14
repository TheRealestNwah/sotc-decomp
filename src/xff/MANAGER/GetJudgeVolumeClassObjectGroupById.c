int *GetJudgeVolumeClassObjectGroupById(char *p, int i)
{
    int *t = *(int **)(p + 0x4);

    if (t != 0) {
        return t + i;
    }
    return 0;
}
