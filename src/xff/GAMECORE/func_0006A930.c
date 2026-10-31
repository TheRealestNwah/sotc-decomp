extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_0006A930(void *surface)
{
    if (*GetCollisionDBAttributeAdr(surface) & 0x2000000000000000) {
        return 0;
    }
    return 1;
}
