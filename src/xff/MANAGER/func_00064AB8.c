extern unsigned long *GetCollisionDBAttributeAdr(void *surf);

static int func_00064AB8(void *a, void *b)
{
    unsigned long t;
    int r;

    t = *GetCollisionDBAttributeAdr(a) & 0x7C000000;
    if (t == 0x34000000 || t == 0x64000000 || t == 0x68000000) {
        return 1;
    }
    t = *GetCollisionDBAttributeAdr(b) & 0x7C000000;
    r = 0;
    if (t == 0x34000000 || t == 0x64000000 || t == 0x68000000) {
        r = 1;
    }
    return r;
}
