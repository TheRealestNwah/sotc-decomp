extern int isysAddGroupWithLinkParam(void *, void *, int, int);

int EntryJudgeVolumeClassObjectGroup(char *p, int i, void *g)
{
    int *t = *(int **)(p + 4);
    if (t != 0) {
        isysAddGroupWithLinkParam(g, t + i, 0, 0);
        return 1;
    }
    return 0;
}
