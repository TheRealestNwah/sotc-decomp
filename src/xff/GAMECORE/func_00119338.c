extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_00119338(void *surface, unsigned long *mask)
{
    return mask[1] == (*GetCollisionDBAttributeAdr(surface) & mask[0]);
}
