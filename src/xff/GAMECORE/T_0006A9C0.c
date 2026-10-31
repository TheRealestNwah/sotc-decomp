extern unsigned long *GetCollisionDBAttributeAdr(void *);

static int T_0006A9C0(void *p, unsigned long *m)
{
    return m[1] == (*GetCollisionDBAttributeAdr(p) & m[0]);
}
