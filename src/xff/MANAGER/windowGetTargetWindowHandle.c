typedef struct { unsigned long pad : 3; unsigned int target : 1; unsigned long rest : 60; } WinFlags;
typedef struct Window { int a; char *obj; char pad[0x14]; struct Window *next; } Window;
extern Window *D_00139BA8;

Window *windowGetTargetWindowHandle(void)
{
    Window *w;
    for (w = D_00139BA8; w != 0; w = w->next) {
        if (((WinFlags *)(w->obj + 0x1B8))->target)
            return w;
    }
    return 0;
}
