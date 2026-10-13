extern void *_impure_ptr;

void srand(long arg0)
{
    (*(unsigned long *)((char *)(_impure_ptr) + 0xA8)) = (unsigned long) ((unsigned long) (arg0 << 0x20) >> 0x20);
}
