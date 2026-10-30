extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_00091500(void *surface)
{
    return (*GetCollisionDBAttributeAdr(surface) & 0xF80000000) != 0x800000000;
}
