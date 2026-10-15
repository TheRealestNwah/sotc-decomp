extern void iosCdSetMode(int mode);

extern int D_00139F04;

void sheetFsSetSpecialFs(int fs, int mode)
{
    D_00139F04 = fs;
    iosCdSetMode(fs != 0 && mode != 0);
}
