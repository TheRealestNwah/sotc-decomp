extern char B_000C5C1C[];
extern int Sg2SlotFindSlotClass(int *out, int cls);
extern void Sg2SlotSetPause(int slot, int pause);

/* Pauses or resumes every slot of the module's slot class. */
void all_soundpause(int mod, int pause)
{
    int list[48];
    int i;

    for (i = Sg2SlotFindSlotClass(list, *(int *)(B_000C5C1C + mod * 0x9B0)) - 1; i >= 0; i--) {
        Sg2SlotSetPause(list[i], pause);
    }
}
