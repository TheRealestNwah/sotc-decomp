extern unsigned long *GetCollisionDBAttributeAdr(void *);

static int T_000CB4D0(void *p)
{
    return (*GetCollisionDBAttributeAdr(p) & 0x3F0) == 0x160;
}
