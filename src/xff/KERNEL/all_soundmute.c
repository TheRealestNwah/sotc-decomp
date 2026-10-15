extern char B_000C5C1C[];
extern int Sg2SlotFindSlotClass(int *out, int cls);
extern void Sg2SlotSetMute(int slot, int mute);

/* Mutes or unmutes every slot of the module's slot class. */
void all_soundmute(int mod, int mute)
{
    int list[48];
    int i;

    for (i = Sg2SlotFindSlotClass(list, *(int *)(B_000C5C1C + mod * 0x9B0)) - 1; i >= 0; i--) {
        Sg2SlotSetMute(list[i], mute);
    }
}
