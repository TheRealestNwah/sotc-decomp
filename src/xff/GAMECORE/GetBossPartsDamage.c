float GetBossPartsDamage(void *arg0, int arg1)
{
    return ((*(float *)((char *)(((arg1 * 0x58) + (*(int *)((char *)(arg0) + 0x10)))) + 0x1C)) - (*(float *)((char *)(((arg1 * 8) + (*(int *)((char *)(arg0) + 0xE8)))) + 0x24))) / (*(float *)((char *)(arg0) + 0x68));
}
