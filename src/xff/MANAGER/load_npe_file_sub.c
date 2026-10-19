extern char *sheetFileGetDataAdrs(int, int);
extern void *func_000C73B8(void *, int);

void load_npe_file_sub(int a, int b, int c)
{
    char *d = sheetFileGetDataAdrs(a, b);
    *(void **)(d + 0x1C) = func_000C73B8((void *)a, c);
}
