typedef int s128 __attribute__((mode(TI)));
extern s128 fltMaxVector;
extern const float RO_0018159C;
extern const float RO_001815A0;

static void func_0010A738(char *p)
{
    *(s128 *)(p + 0x50) = *(s128 *)(p + 0x10);
    *(float *)(p + 0x60) = RO_0018159C;
    *(int *)(p + 0xA0) = 0;
    *(float *)(p + 0xA4) = RO_001815A0;
    *(float *)(p + 0xA8) = RO_0018159C;
    *(int *)(p + 0xD4) = 0;
    *(s128 *)(p + 0xE0) = fltMaxVector;
}
