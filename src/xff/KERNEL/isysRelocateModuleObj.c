/* Relocates a module object once; bit 0x20000000 at +0x2C marks it done.
   The register pin keeps the 0 argument in the beqz delay slot. */
extern void func_00007810(void *, int);
void isysRelocateModuleObj(char *object)
{
    int flag = 0x20000000;
    register int arg asm("$5") = 0;
    if (*(int *)(object + 0x2C) & flag) {
        func_00007810(object, arg);
        return;
    }
    func_00007810(object, 1);
    *(int *)(object + 0x2C) |= flag;
}
