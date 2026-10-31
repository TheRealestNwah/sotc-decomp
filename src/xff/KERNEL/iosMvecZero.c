typedef int s128 __attribute__((mode(TI)));

void iosMvecZero(s128 *v)
{
    s128 t;
    __asm__("daddu %0, $0, $0" : "=r"(t));
    *v = t;
}
