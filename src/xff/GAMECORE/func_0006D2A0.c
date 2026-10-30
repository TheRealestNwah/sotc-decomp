extern int arrowFilter(void *surface);
extern unsigned long *GetCollisionDBAttributeAdr(void *surface);

static int func_0006D2A0(void *surface)
{
    if (arrowFilter(surface) == 0) {
        return 0;
    }
    if (*GetCollisionDBAttributeAdr(surface) & 1) {
        return 0;
    }
    return 1;
}
