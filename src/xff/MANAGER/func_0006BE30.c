extern long *GetCollisionDBAttributeAdr(void *);

static int func_0006BE30(void *collision)
{
    long attr = *GetCollisionDBAttributeAdr(collision);

    if ((attr & 0x7C00) == 0x3C00) {
        return 0;
    }
    return (attr & 0x7C000000) != 0x14000000;
}
