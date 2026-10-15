extern void *memcpy(void *dst, const void *src, unsigned int n);

void _SetLetterKindVariable(void *dst, const void *src, unsigned int n)
{
    memcpy(dst, src, n);
}
