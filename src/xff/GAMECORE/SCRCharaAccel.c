extern void *GetCharacterClass(void *);

void SCRCharaAccel(void *actor, int control, float delta)
{
    void *character;

    character = GetCharacterClass(actor);
    if (*(int *)((char *)character + 0x818) != 0) {
        *(float *)((char *)character + 0x81C) += delta;
        if (*(int *)((char *)character + 0x814) != 0) {
            *(int *)((char *)character + 0x814) = 0;
        }
    } else {
        *(volatile int *)((char *)character + 0x814) = 1;
        *(volatile float *)((char *)character + 0x81C) = 0.0f;
        *(volatile int *)((char *)character + 0x818) = 1;
    }
    *(int *)((char *)character + 0x7EC) = control;
    if ((float)control == 0.0f) {
        *(float *)((char *)character + 0x7E4) = -1.0f;
    }
}
