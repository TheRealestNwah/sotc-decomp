extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_00007E78(void *surface)
{
    unsigned long attribute = *GetCollisionDBAttributeAdr(surface);
    unsigned long flags = attribute & (0xF800UL << 20);
    unsigned long kind = attribute & 0x7C000000UL;

    if (flags == (0x8000UL << 18) || flags == (0xB800UL << 20) || flags == (0xC000UL << 18) ||
        flags == (0xA000UL << 19) || flags == (0xE000UL << 18) || kind == 0x04000000 || kind == 0x34000000 ||
        kind == 0x64000000 || kind == 0x6C000000 || kind == 0x24000000 || kind == 0x68000000)
        return 0;
    return 1;
}
