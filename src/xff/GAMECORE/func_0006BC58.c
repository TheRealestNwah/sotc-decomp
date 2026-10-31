extern long *GetCollisionDBAttributeAdr(void *);

static int func_0006BC58(void *collision, long *mask)
{
    return mask[1] == (*GetCollisionDBAttributeAdr(collision) & mask[0]);
}
