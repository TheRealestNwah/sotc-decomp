typedef struct Ptn Ptn;

typedef struct SheetItem {
    char name[0x20];
    int id20;
    int id24;
    int value;
    int w2C;
    int w30;
    int w34;
    int w38;
    int w3C;
    int w40;
    int w44;
} SheetItem;

typedef struct Menu {
    int w0;
    int x;
    int y;
    SheetItem *items;
    int count;
    void (*func)(void);
    int w44;
    int arg;
    int pad4C;
    int w50;
    int w54;
    int w58;
} Menu;

typedef struct SheetMenu {
    int x;
    int y;
    char *data;
    int count;
    int offset;
    int stride;
    int w18;
    int w1C;
    int w20;
    int w24;
    int w28;
    Menu menu;
} SheetMenu;

extern Ptn rootPtn;
extern void *iosMallocAlign(Ptn *, int, int);
extern void iosSPrintf(char *, const char *, ...);
extern void func_000D4540(void);
extern void createMenu(Menu *, int);

#ifdef NONMATCHING
/* 33 diffs: s0/s1 and s3/s4 swapped and menu field stores scheduled differently */
void createSheetMenu(SheetMenu *s, int arg)
{
    int i = 0;
    SheetItem *items;

    s->menu.x = s->x;
    s->menu.y = s->y;
    items = iosMallocAlign(&rootPtn, s->count * sizeof(SheetItem), 4);
    s->menu.items = items;
    s->menu.count = s->count;
    s->menu.func = func_000D4540;
    s->menu.w44 = s->w28;
    s->menu.arg = arg;
    s->menu.w50 = 1;
    s->menu.w54 = s->w18;
    s->menu.w58 = 1;
    for (; i < s->menu.count; i++) {
        iosSPrintf(items[i].name, "sheet_%02d", i);
        items[i].id20 = i;
        items[i].id24 = i;
        items[i].value = *(int *)(s->data + (s->offset + s->stride * i));
        items[i].w2C = 0;
        items[i].w30 = 0;
        items[i].w34 = 0;
        items[i].w38 = s->w20;
        items[i].w3C = s->w24;
        items[i].w40 = 0;
        items[i].w44 = s->w1C;
    }
    createMenu(&s->menu, arg);
}
#endif
