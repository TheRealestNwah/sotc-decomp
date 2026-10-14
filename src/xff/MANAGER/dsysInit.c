extern int dsysFileInit();
extern int nicosysdInit();

int dsysInit(void)
{
    dsysFileInit();
    return nicosysdInit();
}
