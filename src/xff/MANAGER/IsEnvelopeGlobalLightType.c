int IsEnvelopeGlobalLightType(char *p)
{
    if (*(int *)(p + 0x110) & 0x20000) {
        return 1;
    }
    return 0;
}
