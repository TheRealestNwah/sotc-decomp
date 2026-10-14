extern void *GetCharacterClass();

void EnableCharacterObjMotionRootRotDynamics(void)
{
    void *temp_a1;
    void *temp_v0;

    temp_v0 = GetCharacterClass();
    temp_a1 = (*(void **)((char *)(temp_v0) + 0x19C));
    (*(unsigned char *)((char *)(temp_v0) + 0x529)) = (unsigned char) (*(unsigned char *)((char *)(temp_v0) + 0xA26));
    (*(long *)((char *)(temp_a1) + 0x40)) = (long) (*(long *)((char *)(temp_v0) + 0xA30));
    (*(long *)((char *)(temp_a1) + 0x48)) = (long) (*(long *)((char *)(temp_v0) + 0xA38));
    (*(long *)((char *)(temp_a1) + 0x50)) = (long) (*(long *)((char *)(temp_v0) + 0xA40));
    (*(long *)((char *)(temp_a1) + 0x58)) = (long) (*(long *)((char *)(temp_v0) + 0xA48));
}
