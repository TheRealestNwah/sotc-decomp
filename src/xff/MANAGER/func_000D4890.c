typedef union {
    int i;
    float f;
} Word;

extern int D_00139720;
extern int D_00139724;
extern void windowSetCursorPosOnWindow(int, float *);

typedef struct {
    char *win;
    signed char key;
    char pad5[0x2C - 0x5];
    float x;
    float y;
    float w;
    float h;
} MenuItem;

static void func_000D4890(MenuItem *item)
{
    float pos[2];

    if (D_00139720 != 0) {
        if ((item->key == 'Y' && D_00139724 != 0) || (item->key == 'N' && D_00139724 == 0)) {
            pos[0] = item->x + item->w * 0.5f;
            pos[1] = item->y + item->h * 0.5f;
            windowSetCursorPosOnWindow(((Word *)(item->win + 0x94))->i, pos);
            D_00139720 = 0;
        }
    }
}
