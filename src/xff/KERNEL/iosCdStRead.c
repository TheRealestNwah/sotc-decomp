#ifdef NONMATCHING
/* Parked: 36 words differ (loop layout, extra branch in original) */
extern long B_0004E580;
extern long B_0004E588;
extern long B_0004E590;
extern char B_00046580[];
extern void *memcpy(void *, const void *, unsigned int);
extern void func_00000068(int);

void iosCdStRead(char *dst, int size)
{
    while (size > 0) {
        if (B_0004E590 >= B_0004E580 && B_0004E590 < B_0004E588) {
            int n = B_0004E588 - B_0004E590;
            if (n >= size)
                n = size;
            memcpy(dst, B_00046580 + (int)(B_0004E590 - B_0004E580), n);
            size -= n;
            dst += n;
            B_0004E590 = n + B_0004E590;
        } else {
            func_00000068(B_0004E590 / 2048);
        }
    }
}
#endif
