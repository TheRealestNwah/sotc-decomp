extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_000CC7C0(void *surface)
{
    return (*GetCollisionDBAttributeAdr(surface) & 0x7C000000) != 0x30000000;
}
