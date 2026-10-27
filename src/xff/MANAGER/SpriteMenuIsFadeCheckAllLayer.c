extern int SpriteMenuIsFadeCheckLayer(unsigned char *, int);
static inline unsigned char *menuData(unsigned char *object)
{
    if (object[8] == 0x21)
        return object + 0x90;
    return 0;
}
int SpriteMenuIsFadeCheckAllLayer(unsigned char *object)
{
    unsigned char *menu = menuData(object);
    int i;
    for (i = 0; i < *(int *)(menu + 8); i++) {
        if (SpriteMenuIsFadeCheckLayer(object, i))
            return 1;
    }
    return 0;
}
