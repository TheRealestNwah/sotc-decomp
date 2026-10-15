extern char *sheetFileGetDataAdrs(int, int);
extern int func_000C73B8(int, int);

void load_npe_file_sub(int a, int b, int c)
{
    char *d = sheetFileGetDataAdrs(a, b);
    *(int *)(d + 0x1C) = func_000C73B8(a, c);
}
