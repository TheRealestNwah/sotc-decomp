extern char *sheetFileGetDataAdrs(void *);
extern void *func_000C73B8(void *, int);

void load_npe_file_sub(void *a, int b, int c)
{
    char *d = sheetFileGetDataAdrs(a);
    *(void **)(d + 0x1C) = func_000C73B8(a, c);
}
