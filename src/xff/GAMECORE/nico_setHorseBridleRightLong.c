extern char *GetSCRCharaAIWorkPtr(void *);
extern void nico_setHorseBridleType(void *, int);

void nico_setHorseBridleRightLong(void *actor)
{
    void *horse = *(void **)(GetSCRCharaAIWorkPtr(actor) + 0x4248);

    if (horse != 0) {
        nico_setHorseBridleType(horse, 2);
    }
}
