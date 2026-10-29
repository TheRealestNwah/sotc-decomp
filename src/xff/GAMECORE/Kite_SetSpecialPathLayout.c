typedef int s128 __attribute__((mode(TI)));
extern void AI_SetAnimalLayout(char *, s128 *, float, float);

void Kite_SetSpecialPathLayout(char *kite, s128 *position, float first, float second)
{
    AI_SetAnimalLayout(kite + 0x1F0, position, first, second);
}
