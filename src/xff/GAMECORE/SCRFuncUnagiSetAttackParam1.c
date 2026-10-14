typedef struct { char pad[0x5AC0]; float unk5AC0; float unk5AC4; float unk5AC8; } UnagiWork;
extern UnagiWork *GetSCRCharaAIWorkPtr();

void SCRFuncUnagiSetAttackParam1(float a, float b, float c)
{
    UnagiWork *w = GetSCRCharaAIWorkPtr();

    w->unk5AC4 = a;
    w->unk5AC8 = b;
    w->unk5AC0 = c;
}
