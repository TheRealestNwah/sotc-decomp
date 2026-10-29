typedef struct {
    char pad[0x380];
    int f380;
    char pad384[0x1C];
    int state;
    char pad3A4[0x64];
    int f408;
} PathWork;

extern void *getSCRDataCtrlWork(void *);
extern int getPathStatus(PathWork *);
int SCRConditionPathStatus(void *actor)
{
    return getPathStatus(getSCRDataCtrlWork(actor));
}
