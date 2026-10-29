typedef struct {
    char pad0[0x380];
    int f380;
    char pad1[0x408 - 0x384];
    int f408;
} Way;

extern void *getSCRDataCtrlWork(void *);
extern int getWayFinish(Way *);
int SCRConditionWayFinish(void *actor)
{
    return getWayFinish(getSCRDataCtrlWork(actor));
}
