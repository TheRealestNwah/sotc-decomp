extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_0005BA88(void *surface)
{
    unsigned long attribute = *GetCollisionDBAttributeAdr(surface);
    unsigned long material = attribute & 0x7C000000UL;
    unsigned long flags = attribute & (0xF800UL << 20);
    unsigned long mode = attribute & (0xF000UL << 30);

    if (flags == (0xA000UL << 18) || material == 0x64000000UL || material == 0x68000000UL ||
        material == 0x6C000000UL || material == 0x24000000UL || mode == (0x8000UL << 28) || flags == (0xC000UL << 18) ||
        flags == (0xA000UL << 19))
        return 0;
    return 1;
}
