extern void *getSCRDataCtrlWork(void *);
extern int getDPGroupID(void *, int);
extern int changedGPIndex(void *, char *, void *);
extern int changedDPGroupID(void *, void *, int, int);

int SCRConditionGPOrDPGroupIDChanged(void *a, int b, int c, int d, int e, int f, int g, int group)
{
    int ret = 0;
    char *w = getSCRDataCtrlWork(a);
    int id = getDPGroupID(a, group);

    if (changedGPIndex(a, w, *(void **)(w + 0x4078)) || changedDPGroupID(a, w, id, -1))
        ret = 1;
    return ret;
}
