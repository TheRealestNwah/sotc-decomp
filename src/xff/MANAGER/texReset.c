typedef struct Node { int used; int a; struct Node *prev; struct Node *next; } Node;
extern Node *D_00136274;
extern float D_00136270;
extern void **B_00148A04;
extern void **B_00148A08;
extern int B_00148A0C;
extern void *iosgluGetCameraContext(void);
extern void vramReset(void);
extern void func_0002EC18(void *, float);

void texReset(int enabled, float scale)
{
    char *camera = iosgluGetCameraContext();
    int i;
    Node *node;
    if (camera)
        D_00136270 = *(float *)(camera + 0xC) / 500.0f;
    for (i = 0; i < B_00148A0C; ++i)
        B_00148A04[i] = B_00148A08[i] = 0;
    vramReset();
    for (node = D_00136274; node; node = node->next) {
        char *object = *(char **)((char *)node->a + 0x28);
        char *texture = *(char **)(object + 0x20);
        char *work = *(char **)(texture + 0xC);
        *(int *)(work + 0x14) = 0;
        *(int *)(work + 0x10) = 0;
        *(int *)(work + 0x1C) = 0;
        *(int *)(work + 0x18) = 0;
        if (enabled)
            func_0002EC18(object, scale);
    }
}
