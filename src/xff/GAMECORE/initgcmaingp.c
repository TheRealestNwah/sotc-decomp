extern char rootPtn[];
extern void *gcCreateScriptObj(void *, int, void *, int, int, int, char *);
extern void func_0000C4E8(void);
extern void D_0000C5A0(void);
extern void D_0000C538(void);
extern void D_0000C5F0(void);

void initgcmaingp(void)
{
    gcCreateScriptObj(func_0000C4E8, 0, rootPtn, 0x1000, 0, 1, "st_gpframeinit");
    gcCreateScriptObj(D_0000C5A0, 0, rootPtn, 0x2000, 0, 10, "st_windowdraw");
    gcCreateScriptObj(D_0000C538, 0, rootPtn, 0x1000, 0, 11, "st_gpframefinish");
    gcCreateScriptObj(D_0000C5F0, 0, rootPtn, 0x1000, 0, 2, "st_lightcolman");
}
