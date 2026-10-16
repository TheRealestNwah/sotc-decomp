typedef int s128 __attribute__((mode(TI)));

extern char *GetCharacterClass(void *);

void updateAimIKWork(void *a, s128 *v)
{
    **(s128 **)(GetCharacterClass(a) + 0x1110) = *v;
}
