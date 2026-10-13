void Kite_SetEventIDList(int arg0, int arg1, unsigned int arg2)
{
    if (arg2 < 0xAU) {
        (*(int *)((char *)(((arg2 * 4) + arg0)) + 0x1BC)) = arg1;
    }
}
