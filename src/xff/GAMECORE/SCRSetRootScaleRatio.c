extern char *GetCharacterClass();

int SCRSetRootScaleRatio(int a, float r)
{
    char *c = GetCharacterClass(a);

    if (c != 0) {
        *(float *)(c + 0x570) = r;
        return 1;
    }
    return 0;
}
