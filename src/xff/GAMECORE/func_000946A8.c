extern long *GetCollisionDBAttributeAdr(void *);

static int func_000946A8(void *collision)
{
    return (*GetCollisionDBAttributeAdr(collision) & 0xF80000000) == 0x780000000;
}
