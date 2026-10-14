extern void *GetCharacterClass(void *);

int MotSpdCtrl_SetSpeed(void *work, void *actor, float speed)
{
    int result;
    int enabled;

    enabled = *(int *)((char *)work + 0x14) != 0;
    result = 0;
    if (enabled) {
        do {
            if (*(unsigned char *)((char *)work + 0x10) != 0) {
                return 0;
            }
            *(float *)((char *)GetCharacterClass(actor) + 0x524) = speed;
            result = 1;
        } while (0);
        return result;
    }
    return result;
}
