typedef int s128 __attribute__((mode(TI)));

void iosMvecAllOne(s128 *v)
{
    s128 t;
    __asm__("pceqw %0, $0, $0" : "=r"(t));
    __asm__("psrlw %0, %1, 31" : "=r"(t) : "r"(t));
    *v = t;
}
