extern char *GetCharacterClass(char *);
extern char *GetScriptLayoutClass(char *);
extern char *GetScriptAnimationClass(char *);
extern void CopyGeometryPointer(void *, void *);
extern void func_000EB038(char *, int *);

int CheckDamageLetter(char *obj, int *letter)
{
    char *damage;
    int *info;

    if (letter[0] != 0) {
        if (letter[0] == 1) {
            info = letter + 4;
            switch (*(unsigned char *)(obj + 8)) {
            case 9:
                damage = GetCharacterClass(obj) + 0x200;
                break;
            case 0xB:
                damage = GetScriptLayoutClass(obj) + 0x230;
                break;
            case 0xD:
                damage = GetScriptAnimationClass(obj) + 0x230;
                break;
            case 0x16:
                damage = obj + 0x290;
                break;
            default:
                damage = 0;
                break;
            }
            *(float *)(damage + 0x50) = 0.0f;
            *(float *)(damage + 0x5C) = *(float *)(info + 1);
            *(int *)(damage + 0x60) = *(float *)(info + 2);
            if ((char *)info[0] == obj) {
                *(int *)damage = 2;
            } else {
                *(int *)damage = 3;
                CopyGeometryPointer(damage + 0x10, info + 4);
            }
        }
    } else {
        func_000EB038(obj, letter + 4);
    }
    return 0;
}
