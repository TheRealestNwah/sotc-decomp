extern void spriteDrawSprite(void *, int, float, float, float, float, float, float, int, int);

static void func_00099118(char *p)
{
    char *s = 0;
    int layer;
    int i;

    if (*(unsigned char *)(p + 8) == 0xE)
        s = p + 0x90;
    if (*(int *)(s + 0x4C) == 0)
        return;
    for (layer = 1; layer < 4; layer++) {
        for (i = 0; i < *(int *)(s + 4); i++) {
            char *obj = (*(char ***)s)[i];
            if (*(unsigned char *)(obj + 0x4C) == layer)
                spriteDrawSprite(obj, *(int *)(s + 0x1C), *(float *)(s + 0xC) + *(float *)(s + 0x14), *(float *)(s + 0x10) + *(float *)(s + 0x18), *(float *)(s + 0x20), *(float *)(s + 0x24), *(float *)(s + 0x28), *(float *)(s + 0x30), *(int *)(s + 0x48), -1);
        }
    }
}
