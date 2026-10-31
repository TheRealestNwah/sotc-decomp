extern unsigned long *GetCollisionDBAttributeAdr(void *);

static int T_0006B070(void *p)
{
    return (*GetCollisionDBAttributeAdr(p) & 0x7C000000) == 0x64000000;
}
