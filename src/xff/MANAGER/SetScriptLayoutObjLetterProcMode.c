extern char *GetScriptAnimationClass(unsigned char *);

void SetScriptLayoutObjLetterProcMode(unsigned char *p, int mode)
{
    char *c;
    if (p[8] == 0xB)
        c = (char *)p + 0x20;
    else if (p[8] == 0xD)
        c = GetScriptAnimationClass(p);
    else
        c = 0;
    *(int *)(c + 0x2D0) = mode;
}
