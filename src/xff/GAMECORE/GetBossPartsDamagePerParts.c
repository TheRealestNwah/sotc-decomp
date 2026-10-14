float GetBossPartsDamagePerParts(void *arg0, int arg1)
{
    float temp_f1;

    temp_f1 = (*(float *)((char *)(((arg1 * 0x58) + (*(int *)((char *)(arg0) + 0x10)))) + 0x1C));
    return (temp_f1 - (*(float *)((char *)(((arg1 * 8) + (*(int *)((char *)(arg0) + 0xE8)))) + 0x24))) / temp_f1;
}
