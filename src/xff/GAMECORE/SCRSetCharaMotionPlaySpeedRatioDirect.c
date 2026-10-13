extern void *GetCharacterClass();

void SCRSetCharaMotionPlaySpeedRatioDirect(float fparg0)
{
    (*(float *)((char *)(GetCharacterClass()) + 0x524)) = fparg0;
}
