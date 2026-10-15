void **GetJudgeVolumeClassObjectGroup(char *volume, unsigned int *attr)
{
    unsigned int index = (*attr >> 18) & 0xFFF;
    void **groups = *(void ***)(volume + 4);

    if (groups != 0) {
        return groups + index;
    }
    return 0;
}
