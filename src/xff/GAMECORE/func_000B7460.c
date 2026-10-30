typedef struct { int a; int b; int c; char pad[0x34 - 0xC]; } AnimalType;
extern char SH_SmallAnimalTypeDEFAULT;

static int *func_000B7460(char *p)
{
    AnimalType *t = *(AnimalType **)((char *)&SH_SmallAnimalTypeDEFAULT + 0x10);
    if (*(int *)(p + 0x10) != 0)
        return &t[*(short *)(p + 0x34)].c;
    return &t[*(short *)(p + 0x34)].b;
}
