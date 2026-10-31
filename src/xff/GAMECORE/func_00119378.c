typedef struct {
    unsigned long mask;
    unsigned long value;
} AttrRange;

extern unsigned long *GetCollisionDBAttributeAdr(void *);

static int func_00119378(void *collision, AttrRange *range)
{
    return (*GetCollisionDBAttributeAdr(collision) & range->mask) >= range->value;
}
