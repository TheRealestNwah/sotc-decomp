#ifdef NONMATCHING
/* Parked: 3 words differ (original sets a1 = 0 in the branch delay slot, before restoring registers) */
extern void func_00007810(void *, int);

void isysRelocateModuleObj(char *object)
{
    if (*(int *)(object + 0x2C) & 0x20000000) {
        func_00007810(object, 0);
    } else {
        func_00007810(object, 1);
        *(int *)(object + 0x2C) |= 0x20000000;
    }
}
#endif
