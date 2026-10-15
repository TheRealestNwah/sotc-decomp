extern char *getSCRDataCtrlWork(void *);
extern int getLastPassagePointIdx(char *);
extern int getLastPassageAreaIdx(char *);
extern char *getPointDataByAreaIdx(char *, int, int);

int SCRConditionLastPassagePointEventID(void *o, int id)
{
    char *w = getSCRDataCtrlWork(o);
    int pi = getLastPassagePointIdx(w);
    char *p = getPointDataByAreaIdx(w, pi, getLastPassageAreaIdx(w));
    if (p != 0 && id == *(short *)(p + 0x1C))
        return 1;
    return 0;
}
