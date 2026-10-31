extern long *GetCollisionDBAttributeAdr(void *);

static int func_0006DFF0(void *collision)
{
    return (*GetCollisionDBAttributeAdr(collision) & 0x7C000000) != 0x34000000;
}
