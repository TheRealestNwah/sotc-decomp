extern int getGoalPointDataByAreaIdx(char *, int, int);
extern int getChildSubPointIdxArrayByAreaIdx(char *, int, int);
extern int getSubPointDataByAreaIdx(char *, int, int);
int getConnectPPointIdx(char *context, int point, int area)
{
    int count = 0;
    char *goal = (char *)getGoalPointDataByAreaIdx(context, point, area);
    int indexAddress = getChildSubPointIdxArrayByAreaIdx(context, point, area);
    if (goal == 0 || indexAddress == 0)
        return 0;
    {
        unsigned int i = 0;
        if (*(unsigned int *)(goal + 0x14) != 0) {
            short *indices = (short *)indexAddress;
            do {
                int subPoint = *indices++;
                char *data = (char *)getSubPointDataByAreaIdx(context, subPoint, area);
                if (*(int *)(data + 0x10) & 2)
                    ++count;
                ++i;
            } while (i < *(unsigned int *)(goal + 0x14));
        }
    }
    return count;
}
