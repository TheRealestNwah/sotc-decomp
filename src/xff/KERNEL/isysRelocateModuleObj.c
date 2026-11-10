#ifdef NONMATCHING
/* Parked: 1 word differs (taken branch: original has daddu a1,zero,zero in the beqz
   delay slot; f == 0 gives sltiu. Constant 0 instead scores 3, epilogue order.) */
extern void func_00007810(void *, int);
void isysRelocateModuleObj(char *object)
{
    int f = *(int *)(object + 0x2C) & 0x20000000;
    if (f) {
        func_00007810(object, f == 0);
        return;
    }
    func_00007810(object, 1);
    *(int *)(object + 0x2C) |= 0x20000000;
}
#endif
