extern char *GetScrLwsOriClass(unsigned char *);
extern void fruitsFlagSet(unsigned int, int);
void nico_setFruitsFlag(unsigned char *object)
{
    char *c = GetScrLwsOriClass(object);
    fruitsFlagSet(*(unsigned int *)(c + 0x121C), *(int *)(c + 0x1224));
}
