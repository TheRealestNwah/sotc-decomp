typedef struct {
    char pad0[0x18];
    float scale;
    char pad1C[0x14];
    int child;
    int sibling;
    int mesh;
    char pad3C[4];
} Node;

typedef struct {
    char pad0[8];
    Node *nodes;
} Model;

typedef int (*NodeCallback)(void *, float, int, float);

extern int iosPushCurrentMatrix(void);
extern int iosSetCurrentMatrix(void *);
extern int iosPopCurrentMatrix(void);

#ifdef NONMATCHING
/* Parked: 3 diffs. Pinning count to $17 fixes the saved-register rotation
 * (was 15). Remaining: in the recursive call's argument setup the Original
 * moves b into $f13 in the beq delay slot after $t0/$t1; ours schedules it
 * first. void-return ios externs, else-first branches, and temporaries for
 * b or count don't change it. */
static void func_0003DB80(int idx, Model *model, char *mats, NodeCallback cb, float a, float b, void *ctx, int *count_)
{
    register int *count __asm__("$17") = count_;
    Node *node;
    int sibling;
    int child;

    do {
        int off = idx * 0x40;

        node = (Node *)((char *)model->nodes + off);
        sibling = node->sibling;
        iosPushCurrentMatrix();
        child = node->child;
        if (node->mesh == -1 || cb(ctx, a, 0, node->scale * b) != 0)
            (*count)++;
        iosSetCurrentMatrix(mats + off);
        if (child != -1)
            func_0003DB80(child, model, mats, cb, a, b, ctx, count);
        else
            cb(ctx, a, 1, node->scale * b);
        iosPopCurrentMatrix();
        idx = sibling;
    } while (sibling != -1);
}
#endif
