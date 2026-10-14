char *getGoalDataHeader(char *p)
{
    int o = *(int *)(p + 0x14);

    if (o != 0) {
        return p + o;
    }
    return 0;
}
