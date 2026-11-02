extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

int character_ikcolattrfilter(void *surface)
{
    unsigned long attribute;
    unsigned long kind, mode, flags;

    attribute = *GetCollisionDBAttributeAdr(surface);
    kind = attribute & 0x7C000000;
    flags = attribute & (0xF800UL << 20);
    mode = attribute & (0xF000UL << 30);
    if (kind == 0x30000000 || kind == 0x04000000 || kind == 0x64000000 || kind == 0x68000000 ||
        kind == 0x6C000000)
        return 0;
    if (kind == 0x24000000 || flags == (0x8000UL << 20) || flags == (0x8000UL << 18) ||
        flags == (0xB800UL << 20) || flags == (0xC000UL << 18) || flags == (0xA000UL << 19) ||
        flags == (0xE000UL << 18) || flags == (0xA000UL << 18) || mode == (0x8000UL << 28))
        return 0;
    return 1;
}
