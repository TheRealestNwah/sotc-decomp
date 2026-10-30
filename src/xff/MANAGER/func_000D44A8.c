typedef struct MenuDef {
    char pad0[4];
    int id;
    char pad8[0x14 - 0x8];
    void (*onDraw)(char *, void *, struct MenuDef *);
    char pad18[0x20 - 0x18];
    int arrow;
} MenuDef;

typedef struct {
    char *win;
    char pad4[0xBC - 0x4];
    MenuDef *def;
} MenuItem;

extern void windowSpriteMenuArrow(char *, int, int);

static void func_000D44A8(MenuItem *item)
{
    MenuDef *def = item->def;
    char *win = item->win;

    if (def->onDraw != 0)
        def->onDraw(win, item, def);
    if ((int)(*(long *)(win + 0x1B8) >> 2) & 1) {
        if (def->arrow != 0)
            windowSpriteMenuArrow(win, *(float *)(win + 0x26C), def->id << 4);
    }
}
