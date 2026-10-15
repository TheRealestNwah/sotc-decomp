extern char *getSCRDataCtrlWork(void *);
extern void execPointListSort(char *, char *, int);
extern int getNearPoint(char *, int, int *, int *, char *, int, int, int);

int SCRConditionCheckWayOrientAttainPlayer(void *a)
{
    int i, j;
    char *w = getSCRDataCtrlWork(a);
    char *l = w + 0x2038;
    execPointListSort(w, l, *(int *)(*(char **)(w + 0x407C) + 0x134));
    return getNearPoint(w, 0, &i, &j, l, *(int *)(*(char **)(w + 0x407C) + 0x134), 1, 1);
}
