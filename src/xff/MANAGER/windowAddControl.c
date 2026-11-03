#ifdef NONMATCHING /* loads get scheduled above the stores into the new control (63 diffs; 55 with -fno-strict-aliasing) */
typedef struct { long long lo, hi; } Q;

typedef struct {
    char *name;
    int a;
    int b;
    char rect[0x10];
    char pad1C[4];
    Q col0;
    Q col1;
    char pad40[4];
    int c;
    int d;
    char pad4C[4];
    int e;
    int f;
} ControlDesc;

typedef struct Control {
    int owner;
    char name[0x20];
    int a;
    int b;
    char rect[0x10];
    Q col[6];
    int state0;
    int state1;
    int stateA8;
    char padAC[0xC];
    int c;
    int d;
    int e;
    int f;
    struct Control *next;
    char padCC[4];
} Control;

typedef struct {
    char pad[0x3E4];
    Control *controls;
} WindowBody;

typedef struct {
    int *heap;
    WindowBody *body;
} Window;

extern void *iosMallocAlign(int heap, int size, int align);
extern int iosSPrintf(char *buf, const char *fmt, ...);

typedef struct { char b[0x10]; } Rect16;

Control *windowAddControl(Window *win, ControlDesc *desc)
{
    Control *ctl = iosMallocAlign(*win->heap, sizeof(Control), 0x10);

    if (ctl != 0) {
        ctl->owner = (int)win->body;
        iosSPrintf(ctl->name, "%s", desc->name);
        ctl->a = desc->a;
        ctl->b = desc->b;
        *(Rect16 *)ctl->rect = *(Rect16 *)desc->rect;
        ctl->col[0] = desc->col0;
        ctl->col[1] = desc->col0;
        ctl->col[2] = desc->col0;
        ctl->col[3] = desc->col1;
        ctl->col[4] = desc->col1;
        ctl->col[5] = desc->col1;
        ctl->state1 = 1;
        ctl->state0 = 1;
        ctl->stateA8 = 0;
        ctl->c = desc->c;
        ctl->d = desc->d;
        ctl->e = desc->e;
        ctl->f = desc->f;
        ctl->next = win->body->controls;
        win->body->controls = ctl;
    }
    return ctl;
}
#endif
