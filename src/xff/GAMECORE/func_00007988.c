extern unsigned long *GetCollisionDBAttributeAdr(void *);

static int func_00007988(void *col)
{
    unsigned long attr = *GetCollisionDBAttributeAdr(col) & (0xF800UL << 20);

    if (attr == (0xC000UL << 18) || attr == (0xA000UL << 19))
        return 1;
    return 0;
}
