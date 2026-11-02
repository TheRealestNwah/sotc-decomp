typedef struct MatrixBuffer {
    char data[0x110];
} MatrixBuffer;

typedef struct LayoutMatrix {
    char pad0[0xC];
    MatrixBuffer *current;
    MatrixBuffer buffer[2];
    char pad230[0x30];
    unsigned short pad260 : 9;
    unsigned short side : 1;
    unsigned long rest : 54;
} LayoutMatrix;

typedef struct LayoutClass {
    char pad0[0x144];
    /* char alias keeps the pointer reloaded after bitfield stores */
    union {
        LayoutMatrix *ptr;
        char alias;
    } matrix;
} LayoutClass;

extern void *GetLayoutDispObjGroup(void *);
extern void **isysGroupForFirst(void *, int);
extern void **isysGroupForNext(void **, int);
extern void isysGroupForExit(void *, int);
extern LayoutClass *GetLayoutClass(void *);

void InitLayoutObjMatrix(void *object)
{
    void *member = 0;
    void **it;

    for (it = isysGroupForFirst(GetLayoutDispObjGroup(object), 0); it != 0;
         it = isysGroupForNext(it, 0)) {
        LayoutClass *layout;
        member = *it;
        layout = GetLayoutClass(member);
        if (layout != 0 && layout->matrix.ptr != 0) {
            layout->matrix.ptr->side ^= 1;
            layout->matrix.ptr->current = &layout->matrix.ptr->buffer[layout->matrix.ptr->side];
        }
    }
    if (member != 0)
        isysGroupForExit(member, 0);
}
