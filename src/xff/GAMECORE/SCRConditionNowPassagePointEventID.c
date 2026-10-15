extern char *getSCRDataCtrlWork(void *);
extern int getNowPassagePointIdx(char *);
extern int getNowPassageAreaIdx(char *);
extern char *getPointDataByAreaIdx(char *, int, int);

int SCRConditionNowPassagePointEventID(void *o, int id)
{
    char *w = getSCRDataCtrlWork(o);
    int pi = getNowPassagePointIdx(w);
    char *p = getPointDataByAreaIdx(w, pi, getNowPassageAreaIdx(w));
    if (p != 0 && id == *(short *)(p + 0x1C))
        return 1;
    return 0;
}
