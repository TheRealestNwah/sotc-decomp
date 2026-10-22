extern int iosCreateSema(int, int, int);
extern unsigned char rootPtn[];
extern void *mallocStartAdrs;
extern int B_0004F5F8;
extern void *func_00002CF8(void *, void *, void *, int);

void iosInitMallocSystem(void *start, void *end, int garbageSize)
{
    B_0004F5F8 = iosCreateSema(1, 1, 0);
    mallocStartAdrs = start;
    func_00002CF8(rootPtn, start, end, garbageSize);
}
