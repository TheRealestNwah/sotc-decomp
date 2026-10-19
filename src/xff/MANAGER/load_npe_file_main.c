extern char *sheetFileGetDataAdrs(int, int);
extern void *func_000C73B8(void *, int);

void load_npe_file_main(int a, int b, int c)
{
    char *d = sheetFileGetDataAdrs(a, b);
    *(void **)(d + 0xC) = func_000C73B8((void *)a, c);
}
