typedef struct {
    char pad[0x5AB0];
    float unk5AB0;
    float unk5AB4;
    float unk5AB8;
    float unk5ABC;
} UnagiWork;

extern UnagiWork *GetSCRCharaAIWorkPtr();

void SCRFuncUnagiSetAttackParam0(float a, float b, float c, float d)
{
    UnagiWork *w = GetSCRCharaAIWorkPtr();

    w->unk5AB0 = a;
    w->unk5AB4 = b;
    w->unk5AB8 = c;
    w->unk5ABC = d;
}
