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

extern void iosPushCurrentMatrix(void);
extern void iosSetCurrentMatrix(void *);
extern void iosPopCurrentMatrix(void);

#ifdef NONMATCHING
/* 20 diffs: saved registers rotate */
static void func_0003DB80(int idx, Model *model, char *mats, NodeCallback cb, float a, float b, void *ctx, int *count)
{
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
