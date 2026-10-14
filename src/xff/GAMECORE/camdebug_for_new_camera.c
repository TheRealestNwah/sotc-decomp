extern char gcGlobalVar[];
extern long iosGetTCountExtension(void);
extern void func_000052B0(void);

void camdebug_for_new_camera(void)
{
    char *g = gcGlobalVar;
    *(long *)(g + 0xD0) = iosGetTCountExtension();
    func_000052B0();
    *(long *)(g + 0xD8) = iosGetTCountExtension();
}
