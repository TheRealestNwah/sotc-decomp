extern unsigned long long *GetCollisionDBAttributeAdr(int);

inline int playerPlaneJudgeFunc(int col) {
    unsigned long long attr = *GetCollisionDBAttributeAdr(col);
    unsigned long long kind = attr & 0x7C000000;
    unsigned long long material = attr & 0xF80000000ULL;
    unsigned long long type = attr & 0x3C0000000000ULL;

    if (kind == 0x34000000 || kind == 0x64000000 || kind == 0x68000000 || kind == 0x6C000000 || kind == 0x24000000 || kind == 0x48000000 || kind == 0x30000000 || kind == 0x04000000 || material == 0x200000000ULL || material == 0xB80000000ULL || material == 0x80000000ULL || material == 0x300000000ULL || material == 0x500000000ULL || material == 0x280000000ULL || type == 0x80000000000ULL)
        return 0;
    return 1;
}

int playerPlaneJudgeFuncCameraFilter(int col) {
    if ((*GetCollisionDBAttributeAdr(col) & 0x7C000000) == 0x24000000)
        return 1;
    return playerPlaneJudgeFunc(col);
}
