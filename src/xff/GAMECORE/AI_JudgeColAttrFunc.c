extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

int AI_JudgeColAttrFunc(void *surface)
{
    unsigned long attribute = *GetCollisionDBAttributeAdr(surface);
    unsigned long flags = attribute & (0xF800UL << 20);
    unsigned long mode = attribute & (0xF000UL << 30);
    unsigned long kind = attribute & 0x7C00UL;

    if (flags == (0x8000UL << 18) || flags == (0xC000UL << 18) || flags == (0xA000UL << 19) ||
        flags == (0xB800UL << 20) || flags == (0xE000UL << 18) || kind == 0x3C00 || kind == 0x4000 ||
        kind == 0x4400 || kind == 0x4C00 || kind == 0x5400 || kind == 0x5C00 || kind == 0x6400 ||
        kind == 0x6C00 || kind == 0x7400 || kind == 0x7C00 || mode == (0x8000UL << 28))
        return 0;
    return 1;
}
