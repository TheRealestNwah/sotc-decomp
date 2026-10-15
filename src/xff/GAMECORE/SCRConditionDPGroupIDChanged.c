extern char *getSCRDataCtrlWork(void *);
extern int getDPGroupID(void *, int);
extern int changedDPGroupID(void *, char *, int, int);

int SCRConditionDPGroupIDChanged(void *a, int b, int c, int d, int e, int f, int g, int name)
{
    char *w = getSCRDataCtrlWork(a);
    return changedDPGroupID(a, w, getDPGroupID(a, name), -1);
}
