extern char *GetScrLwsOriClass();
extern int fruitsFlagSet();

int nico_setFruitsFlag(void)
{
    char *c = GetScrLwsOriClass();

    return fruitsFlagSet(*(int *)(c + 0x121C), *(int *)(c + 0x1224));
}
