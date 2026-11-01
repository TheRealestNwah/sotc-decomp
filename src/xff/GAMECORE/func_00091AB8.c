extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static long func_00091AB8(void *surface)
{
    unsigned long attribute = *GetCollisionDBAttributeAdr(surface);
    unsigned long flags = attribute & (0xF800UL << 20);
    unsigned long kind;

    if (flags == (0xC000UL << 18) || flags == (0xA000UL << 19))
        return 0;
    if (flags != (0xA000UL << 18)) {
        kind = attribute & 0x7C000000;
        if (kind != 0x30000000 && kind != 0x34000000 && kind != 0x6C000000 && kind != 0x24000000 &&
            kind != 0x04000000 && kind != 0x64000000) {
            long r = (attribute & (0xF000UL << 30)) != (0x8000UL << 28);
            if (kind != 0x68000000)
                return r;
        }
    }
    return 0;
}
