extern char *getSCRDataCtrlWork(void *);
extern int getNowPassagePointIdx(char *);
extern int getNowPassageAreaIdx(char *);
extern char *getPointDataByAreaIdx(char *, int, int);

int SCRConditionNowPassagePointEventIDRange(void *actor, int lo, int hi)
{
    char *work = getSCRDataCtrlWork(actor);
    int point = getNowPassagePointIdx(work);
    char *data = getPointDataByAreaIdx(work, point, getNowPassageAreaIdx(work));
    int id;

    if (data != 0) {
        for (id = lo; id <= hi; id++) {
            if (id == *(short *)(data + 0x1C))
                return 1;
        }
    }
    return 0;
}
