typedef int s128 __attribute__((mode(TI)));

typedef union {
    s128 q;
    float f[4];
} Vec4;

typedef struct {
    char pad[0x134];
    Vec4 *pos;
} LayoutClass;

typedef struct {
    char pad[0x40];
    int status;
    char pad44[0xC];
    Vec4 pos;
} TempBase;

extern LayoutClass *GetLayoutClass(void *);

void setTmpBasePos(void *object, TempBase *base)
{
    LayoutClass *layout = GetLayoutClass(object);
    s128 position = layout->pos->q;

    base->status = -1;
    base->pos.q = position;
}
