static int func_000C5BD0(char *a, char *b, char *c)
{
    if (*(int *)(a + 0x110) == 0 && (*(int *)(b + 0x64) != 0 || *(int *)(b + 0xB0) == 1 || *(int *)(c + 0x164) == 2))
        return 1;
    else
        return 0;
}
