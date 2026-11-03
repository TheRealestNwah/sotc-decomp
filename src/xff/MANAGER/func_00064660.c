extern unsigned long *GetCollisionDBAttributeAdr(void *);

static int func_00064660(void *a)
{
    return (*GetCollisionDBAttributeAdr(a) & 0x7C000000) != 0x30000000;
}
