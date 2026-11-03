extern unsigned long *GetCollisionDBAttributeAdr(void *);

static int func_000EBC78(void *db)
{
    unsigned long attr = *GetCollisionDBAttributeAdr(db);
    unsigned long kind = attr & 0xF80000000UL;
    unsigned long type = attr & 0x7C000000;

    if (kind == 0x300000000UL || kind == 0x500000000UL || kind == 0x280000000UL || kind == 0x200000000UL || kind == 0xB80000000UL || kind == 0x380000000UL || kind == 0x800000000UL || kind == 0x100000000UL) return 0;
    if (type == 0x30000000 || type == 0x34000000 || type == 0x6C000000 || type == 0x24000000 || type == 0x64000000 || type == 0x68000000) return 0;
    return 1;
}
