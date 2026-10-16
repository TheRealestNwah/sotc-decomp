typedef struct {
    char geo[0x40];
    void *from;
    int ctrl;
    int pad48;
    int pad4C;
    int type;
    char pad[0xC];
} CtrlMsg;

extern char *GetCharacterClass(void *);
extern void CopyGeometryPointer(void *, void *);
extern void _isysSendSubMsg(void *, void *, int);

int SendCharaControlledChangeMsg(void *a, void *b, void *geo)
{
    char *ca = GetCharacterClass(a);
    char *cb = GetCharacterClass(b);
    CtrlMsg msg;

    if (ca == 0)
        return 0;
    msg.from = b;
    msg.type = 2;
    CopyGeometryPointer(&msg, geo);
    msg.ctrl = *(int *)(cb + 0x754);
    _isysSendSubMsg(ca + 0x10D0, &msg, 0x60);
    return 1;
}
