typedef struct { char pad[0xA8]; unsigned long next; } Reent;
extern Reent *_impure_ptr;

int rand(void)
{
    Reent *r = _impure_ptr;
    r->next = r->next * 0x5851F42D4C957F2DUL + 1;
    return (int)((r->next >> 32) & 0x7FFFFFFF);
}
