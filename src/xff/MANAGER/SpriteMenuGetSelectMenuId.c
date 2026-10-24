typedef struct {
    unsigned unused_low : 11;
    signed id : 10;
    unsigned unused_high : 11;
} MenuBits;

typedef struct {
    char pad[56];
    MenuBits bits;
    char tail[8];
} MenuEntry;

typedef struct {
    char pad[4];
    unsigned menus;
    int unused;
    int select;
} SpriteMenu;

static inline int getSelectMenuIdBySpriteMenuClass(SpriteMenu *menu)
{
    int index = menu->select;
    MenuBits *bits;
    if (index != -1) {
        bits = &((MenuEntry *)(menu->menus + index * 68))->bits;
        return bits->id;
    }
    return -1;
}

int SpriteMenuGetSelectMenuId(unsigned char *p)
{
    return getSelectMenuIdBySpriteMenuClass((SpriteMenu *)(p[8] == 0x21 ? p + 0x90 : 0));
}
