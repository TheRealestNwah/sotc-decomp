typedef struct {
    char pad0[0x3CA4];
    int f3CA4;
    int f3CA8;
    int f3CAC;
} PathEx;

extern void *getSCRDataCtrlWork(void *);
extern int getPathExFinish(PathEx *, int);
int SCRConditionPPFinish(void *actor)
{
    return getPathExFinish(getSCRDataCtrlWork(actor), 9);
}
