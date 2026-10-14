extern void *GetCharacterClass(void *);

void SCRSetCharaMotionPlaySpeedRatioDirect(void *actor, float fparg0)
{
    (*(float *)((char *)(GetCharacterClass(actor)) + 0x524)) = fparg0;
}
