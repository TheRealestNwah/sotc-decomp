typedef int s128 __attribute__((mode(TI)));

void iosMvecAllOnes(s128 *v)
{
    s128 t;
    __asm__("pceqw %0, $0, $0" : "=r"(t));
    *v = t;
}
