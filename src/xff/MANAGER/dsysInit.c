extern void dsysFileInit(void);
extern int nicosysdInit(void);

int dsysInit(void)
{
    dsysFileInit();
    return nicosysdInit();
}
