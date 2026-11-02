extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

int pathJudgeFunc(void *surface)
{
    unsigned long attribute;
    unsigned long kind, mode, flags;

    attribute = *GetCollisionDBAttributeAdr(surface);
    flags = attribute & (0xF800UL << 20);
    kind = attribute & 0x7C000000;
    mode = attribute & (0xF000UL << 30);
    if (attribute & (0x8000UL << 46))
        return 0;
    if (flags == (0x8000UL << 18) || flags == (0xB800UL << 20) || kind == 0x7C000000)
        return 1;
    if (kind == 0x64000000 || kind == 0x68000000 || kind == 0x6C000000)
        return 0;
    if (kind == 0x24000000 || flags == (0xC000UL << 18) || flags == (0xA000UL << 19) || flags == (0xA000UL << 18) ||
        flags == (0xE000UL << 18) || mode == (0x8000UL << 28))
        return 0;
    return 1;
}
