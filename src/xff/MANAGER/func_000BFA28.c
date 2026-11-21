/* Parked: 4 diffs. Draws an emitter node chain: picks the display layer from the emitter mode, then draws runs of nodes sharing an owner key (singly, or sorted through a VLA). Remaining: the original if-converts the k == 2 layer choice with movz at 0xE8-0xF4; gcc keeps branches. */
#ifdef NONMATCHING
typedef struct Node {
    char *owner;
    char pad4[0x128 - 4];
    int index;
    char pad12c[0x1B0 - 0x12C];
    struct Node *next;
} Node;

extern int B_00149A90;
extern int T_000C5C18(char **a, char **b);
extern void func_000C5C40(Node *n, void *mtx, void *pos);
extern void modelResetSurface(int);
extern void iosDlPushLayer(int);
extern void iosDlPopLayer(void);
extern void qsort(void *, unsigned int, unsigned int, void *);

static void func_000BFA28(Node *node, void *mtx, void *pos)
{
    char *ctx;
    char *res;
    int k;
    register int two asm("t0");
    int layer;
    Node *start;
    int n;
    int i;
    Node **p;

    if (node == 0) {
        return;
    }
    ctx = *(char **)(node->owner + 0x48);
    res = *(char **)(ctx + 0xD4) + node->index * 0x1BC;
    layer = 0xB;
    if (*(int *)(ctx + 0xC0) == 1 && B_00149A90 == 0) {
        return;
    }
    two = 2;
    if (*(int *)(ctx + 0xC0) == two && B_00149A90 == 1) {
        return;
    }
    if (*(int *)(res + 0xC) == 4) {
        layer = 0x13;
    } else {
        k = *(int *)(ctx + 0xC4);
        if (B_00149A90 == 0) {
            if (k == 0) {
                layer = 0x12;
            }
        } else {
            if (k == 1) {
                layer = 0x12;
            } else if (k == 0) {
            } else if (k == two) {
                layer = 0x16;
            }
        }
    }
    if (layer == 0x12) {
        modelResetSurface(0x12);
    }
    iosDlPushLayer(layer);
    do {
        start = node;
        n = 0;
        do {
            node = node->next;
            n++;
        } while (node != 0 && *(int *)(node->owner + 0x34) == *(int *)(start->owner + 0x34));
        if (n < 2) {
            func_000C5C40(start, mtx, pos);
        } else {
            Node *arr[n];
            Node *q;

            q = start;
            for (i = 0; i < n; i++) {
                arr[i] = q;
                q = q->next;
            }
            qsort(arr, n, 4, T_000C5C18);
            for (i = 0; i < n; i++) {
                func_000C5C40(arr[i], mtx, pos);
            }
        }
    } while (node != 0);
    iosDlPopLayer();
}
#endif
