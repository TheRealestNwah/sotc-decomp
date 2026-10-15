extern char *getSCRDataCtrlWork(void *);
extern char *getPassageWork(char *, int);
extern char *getPointDataByAreaIdx(char *, int, int);

int SCRConditionNextPointEventID(void *a, int id)
{
    char *pt;
    char *w = getSCRDataCtrlWork(a);
    char *p = getPassageWork(w, 0);
    if (p != 0) {
        pt = getPointDataByAreaIdx(w, *(short *)(p + 0x14), *(int *)(p + 0x1C));
        if (pt != 0 && id == *(short *)(pt + 0x1C))
            return 1;
    }
    return 0;
}
