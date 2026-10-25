typedef struct Node { int used; int a; struct Node *prev; struct Node *next; } Node;
extern Node *D_00136274;
extern float D_00136270;
extern int D_00136268;
extern char B_00148A00[];
extern void **B_00148A04;
extern void **B_00148A08;
extern int B_00148A0C;
extern char rootPtn[];
extern void isysInitGroup(void *);
extern void *iosMallocAlign(void *, int, int);
extern void *iosgluGetCameraContext(void);
extern void vramReset(void);

/* Union access (alias set 0) keeps the next-link load after the stores. */
typedef union TexWorkUV {
    struct {
        char pad0[0x10];
        int s10;
        int s14;
        int s18;
        int s1C;
    } f;
    int raw[8];
} TexWorkUV;

void texInit(int count)
{
    char *camera;
    int i;
    Node *node;

    B_00148A0C = count;
    isysInitGroup(B_00148A00);
    B_00148A04 = iosMallocAlign(rootPtn, B_00148A0C * 4, 0x10);
    B_00148A08 = iosMallocAlign(rootPtn, B_00148A0C * 4, 0x10);
    camera = iosgluGetCameraContext();
    if (camera)
        D_00136270 = *(float *)(camera + 0xC) / 500.0f;
    for (i = 0; i < B_00148A0C; ++i)
        B_00148A04[i] = B_00148A08[i] = 0;
    vramReset();
    for (node = D_00136274; node; node = node->next) {
        char *object = *(char **)((char *)node->a + 0x28);
        char *texture = *(char **)(object + 0x20);
        TexWorkUV *work = *(TexWorkUV **)(texture + 0xC);
        work->f.s14 = 0;
        work->f.s10 = 0;
        work->f.s1C = 0;
        work->f.s18 = 0;
    }
    D_00136268 = 1;
}
