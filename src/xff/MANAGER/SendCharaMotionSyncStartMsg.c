typedef struct { int arg; char pad[0x4C]; int type; char pad2[0xC]; } CharaMsg;
extern char *GetCharacterClass(void *);
extern void _isysSendSubMsg(void *, CharaMsg *, int);

int SendCharaMotionSyncStartMsg(void *actor, int arg)
{
    CharaMsg m;
    char *c = GetCharacterClass(actor);
    if (c == 0)
        return 0;
    m.arg = arg;
    m.type = 3;
    _isysSendSubMsg(c + 0x10D0, &m, sizeof(m));
    return 1;
}
