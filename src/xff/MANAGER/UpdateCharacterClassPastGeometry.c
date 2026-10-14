typedef int s128 __attribute__((mode(TI)));
extern void UpdateLayoutClassPastGeometry(char *);

void UpdateCharacterClassPastGeometry(char *c)
{
    *(s128 *)(c + 0x500) = **(s128 **)(c + 0x138);
    UpdateLayoutClassPastGeometry(c);
    *(s128 *)(c + 0x4D0) = *(s128 *)(c + 0x4C0);
}
