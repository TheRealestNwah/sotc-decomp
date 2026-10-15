extern char *GetCharacterClass(void *);

void SCRCharaTurn(void *o, float t)
{
    float v = *(float *)(GetCharacterClass(o) + 0x7E8) * 0.9f;
    t = t * 0.1f;
    *(float *)(GetCharacterClass(o) + 0x7E8) = v + t;
}
