typedef int s128 __attribute__((mode(TI)));
extern char gcGlobalVar[];

void SetCamFinalizerGeometry(s128 *a, s128 *b)
{
    s128 *dst = (s128 *)(gcGlobalVar + 0x340);
    dst[0] = *a;
    dst[2] = *b;
}
