typedef int s128 __attribute__((mode(TI)));
extern s128 fltMaxVector;
extern const float RO_001814C0;
extern const float RO_001814C4;

static void func_001071B0(char *p)
{
    *(s128 *)(p + 0x60) = *(s128 *)(p + 0x10);
    *(float *)(p + 0x70) = RO_001814C0;
    *(int *)(p + 0xE4) = 0;
    *(float *)(p + 0xE8) = RO_001814C4;
    *(float *)(p + 0xEC) = RO_001814C0;
    *(int *)(p + 0xF4) = 0;
    *(s128 *)(p + 0x100) = fltMaxVector;
}
