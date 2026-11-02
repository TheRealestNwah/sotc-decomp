extern unsigned long long *GetCollisionDBAttributeAdr(void);

int pathJudgeFunc(void) {
    unsigned long long attr = *GetCollisionDBAttributeAdr();
    unsigned long long material = attr & 0xF80000000ULL;
    unsigned long long km = 0x7C000000;
    unsigned long long flag = attr & 0x2000000000000000ULL;
    unsigned long long type = attr & 0x3C0000000000ULL;
    unsigned long long kind = attr & km;

    if (flag)
        return 0;
    if (material == 0x200000000ULL || material == 0xB80000000ULL || kind == km)
        return 1;
    if (kind == 0x64000000 || kind == 0x68000000 || kind == 0x6C000000 || kind == 0x24000000 || material == 0x300000000ULL || material == 0x500000000ULL || material == 0x280000000ULL || material == 0x380000000ULL || type == 0x80000000000ULL)
        return 0;
    return 1;
}
