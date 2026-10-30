extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_001205B0(void *surface)
{
    return (*GetCollisionDBAttributeAdr(surface) & 0xF80000000) == 0x600000000;
}
