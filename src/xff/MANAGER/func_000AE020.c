extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_000AE020(void *surface)
{
    return (*GetCollisionDBAttributeAdr(surface) & 0xF80000000) != 0x280000000;
}
