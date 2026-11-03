typedef struct {
    float x, y, w, h;
} Rect;

typedef struct {
    int top;
    int pad;
    int count;
} ListState;

extern void windowSpriteNoTex(void *, Rect *, void *, float);
extern void windowCursorBlink(void *, void *);
extern int D_00139700[];

static void func_000D42F8(void *unused, char *w)
{
    int color[4];
    ListState *list = *(ListState **)(w + 0x3E8);
    float width = *(float *)(w + 0x26C);
    char *data = *(char **)(w + 0x3E0);
    float height = *(float *)(w + 0x270);

    windowCursorBlink(color, D_00139700);
    if (list->count > 0) {
        Rect r = (Rect){ width - 6.0f, 2.0f - *(float *)(w + 0x19C), 4.0f, 4.0f };
        windowSpriteNoTex(w, &r, color, 16777215.0f);
    }
    if (list->count + list->top < *(int *)(data + 0x10)) {
        Rect r = (Rect){ width - 6.0f, height - *(float *)(w + 0x19C) - 6.0f, 4.0f, 4.0f };
        windowSpriteNoTex(w, &r, color, 16777215.0f);
    }
}
