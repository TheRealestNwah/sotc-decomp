int IsEnvelopeGameLightType(char *p)
{
    if (*(int *)(p + 0x2C) & 0x20000) {
        return 1;
    }
    return 0;
}
