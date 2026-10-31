extern long *GetCollisionDBAttributeAdr(void *);

static int func_00125B30(void *collision)
{
    return (*GetCollisionDBAttributeAdr(collision) & 0x7C000000) != 0x30000000;
}
