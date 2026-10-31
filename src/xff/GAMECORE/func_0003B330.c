extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static unsigned long func_0003B330(void *surface)
{
    return (*GetCollisionDBAttributeAdr(surface) >> 46) & 1;
}
