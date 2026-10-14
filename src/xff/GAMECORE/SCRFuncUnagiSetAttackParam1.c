typedef struct { char pad[0x5AC0]; float unk5AC0; float unk5AC4; float unk5AC8; } UnagiWork;
extern void *GetSCRCharaAIWorkPtr(void *);

void SCRFuncUnagiSetAttackParam1(void *actor, float a, float b, float c)
{
    UnagiWork *w = ((UnagiWork *)GetSCRCharaAIWorkPtr(actor));

    w->unk5AC4 = a;
    w->unk5AC8 = b;
    w->unk5AC0 = c;
}
