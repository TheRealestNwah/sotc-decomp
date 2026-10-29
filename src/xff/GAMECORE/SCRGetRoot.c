typedef int s128 __attribute__((mode(TI)));
extern char *GetLayoutClass(unsigned char *);
void SCRGetRoot(s128 *out, unsigned char *object)
{
    *out = **(s128 **)(GetLayoutClass(object) + 0x134);
}
