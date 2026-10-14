typedef int s128 __attribute__((mode(TI)));

extern char *GetLayoutClass();

void SCRGetRoot(s128 *out, int a)
{
    *out = **(s128 **)(GetLayoutClass(a) + 0x134);
}
