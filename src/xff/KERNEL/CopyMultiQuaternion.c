typedef int s128 __attribute__((mode(TI)));

void CopyMultiQuaternion(s128 *dst, s128 *src, int n)
{
    int i;
    for (i = 0; i < n; i++)
        dst[i] = src[i];
}
