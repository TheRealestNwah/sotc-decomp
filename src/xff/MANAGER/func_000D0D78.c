#ifdef NONMATCHING
/* Parked: 30 words differ (register allocation and scheduling) */
typedef struct { long a; long b; } R16;
typedef struct Node {
    void **win;
    char pad4[0x18];
    struct Node *next;
    char pad20[8];
    int sel;
    int active;
} Node;
typedef struct {
    char pad0[4];
    int id;
    char pad8[0x10];
    void (*onSelect)(void *, void *, void *);
    void (*onDecide)(void *, void *, void *, int);
    void *submenu;
    int keep;
} Item;
typedef struct {
    char *owner;
    char pad4[0x3C];
    R16 r40;
    R16 r50;
    char pad60[0x10];
    R16 r70;
    R16 r80;
    R16 r90;
    int iA0;
    int iA4;
    int iA8;
    char padAC[8];
    int flags;
    char padB8[4];
    Item *item;
} Win;
extern void createMenu(void *, void *);
extern void windowCloseRequest(void *);
extern void windowCursorBlink(void *, void *);
extern void windowGetCursorPosOnWindow(int, float *);
extern void windowSetCursorPosOnWindow(int, float *);
void func_000D0D78(Win *w)
{
    char *o = w->owner;
    char **po = &o;
    Item *it = w->item;
    Node *n;
    Node *p;
    float pos[2];

    n = *(Node **)(o + 0x3E0);
    if (it->onSelect != 0)
        it->onSelect(o, w, it);
    if ((w->flags & 1) && n->active != 0) {
        n->sel = it->id;
        windowCursorBlink(&w->r40, (char *)w + 0x60);
        w->r70 = w->r90;
        w->iA0 = w->iA8;
    } else {
        w->r40 = w->r50;
        w->r70 = w->r80;
        w->iA0 = w->iA4;
    }
    if (w->flags & 0x20020) {
        if (it->onDecide != 0)
            it->onDecide(o, w, it, w->flags);
        if (it->submenu != 0) {
            windowGetCursorPosOnWindow(*(int *)(o + 0x94), pos);
            pos[0] += 56.0f;
            pos[1] += 32.0f;
            windowSetCursorPosOnWindow(*(int *)(o + 0x94), pos);
            createMenu(it->submenu, n);
        } else if (it->keep == 0) {
            for (p = n; p != 0; p = p->next)
                windowCloseRequest(p->win[1]);
        }
    } else if (w->flags & 0x40040) {
        windowCloseRequest(*po);
    }
}
#endif
