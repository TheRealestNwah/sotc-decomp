extern char *sheetFileGetDataAdrs(void *);
extern int func_000C73B8(void *, int);

void load_npe_file_main(void *a, int b, int c)
{
    char *d = sheetFileGetDataAdrs(a);
    *(int *)(d + 0xC) = func_000C73B8(a, c);
}
