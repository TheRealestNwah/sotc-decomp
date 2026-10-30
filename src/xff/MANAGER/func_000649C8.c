extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static inline int isHit(unsigned long material)
{
    int r = 0;
    if (material == 0x34000000UL || material == 0x64000000UL || material == 0x68000000UL)
        r = 1;
    return r;
}

static int func_000649C8(void *surface, signed char *opt)
{
    unsigned long attribute = *GetCollisionDBAttributeAdr(surface);
    unsigned long material = attribute & 0x7C000000UL;
    int hit;

    if (opt[0] != 0 && material == 0x14000000UL)
        return 0;
    if (opt[1] == 0 && (attribute & (0xF800UL << 20)) == (0x9000UL << 19))
        return 0;
    opt[4] = isHit(material);
    hit = opt[4];
    if (opt[2] != 0) {
        if (hit == 0)
            return 1;
        if ((attribute & (0x8000UL << 47)) == 0)
            return 0;
    }
    return 1;
}
