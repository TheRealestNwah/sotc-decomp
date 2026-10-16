int InitAmbientLightObj(unsigned char *o, int *v)
{
    int *c = (int *)(o[8] == 0x14 ? o + 0x1C : 0);
    c[0] = v[0];
    c[1] = v[1];
    c[2] = v[2];
    return 1;
}
