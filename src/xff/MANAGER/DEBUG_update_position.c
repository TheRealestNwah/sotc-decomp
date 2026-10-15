typedef int s128 __attribute__((mode(TI)));
extern int D_0012FDE4;
extern int (*D_0012FDEC)(s128 *, s128 *);

int DEBUG_update_position(s128 *out, s128 *in)
{
    if (D_0012FDE4 != 0 && D_0012FDEC != 0)
        return D_0012FDEC(out, in);
    *out = *in;
    return 0;
}
