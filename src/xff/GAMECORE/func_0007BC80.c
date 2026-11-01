extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_0007BC80(void *surface)
{
    unsigned long attribute;
    unsigned long kind, mode, flags;
    int r;

    if ((*GetCollisionDBAttributeAdr(surface) & (0xFE00UL << 38)) == (0x9400UL << 38))
        return 0;
    attribute = *GetCollisionDBAttributeAdr(surface);
    kind = attribute & 0x7C000000;
    flags = attribute & (0xF800UL << 20);
    mode = attribute & (0xF000UL << 30);
    if (kind == 0x34000000 || kind == 0x64000000 || kind == 0x68000000 || kind == 0x6C000000 ||
        kind == 0x24000000 || kind == 0x48000000 || kind == 0x30000000 || kind == 0x04000000 ||
        flags == (0x8000UL << 18) || flags == (0xB800UL << 20) || flags == (0x8000UL << 16) ||
        flags == (0xC000UL << 18) || flags == (0xA000UL << 19) || flags == (0xA000UL << 18) ||
        mode == (0x8000UL << 28))
        r = 0;
    else
        r = 1;
    return r;
}
