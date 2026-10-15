extern void GetMotionMatrix(int, int, int, int, char *, char *);

int CalcCharacterClassBaseGeo(char *c)
{
    int r = *(signed char *)(c + 0x533);
    if (r == 0) {
        GetMotionMatrix(*(int *)(c + 0x344), *(int *)(c + 0x348), *(int *)(c + 0x358), *(int *)(c + 0x340), c + 0x40, c + 0x90);
        c[0x533] = 1;
    }
    return r;
}
