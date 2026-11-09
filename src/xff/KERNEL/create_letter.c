typedef struct {
    int x0;
    int size;
    void (*init)(void *);
    int xC;
    int extra;
    void (*post)(void *);
} LetterType;

typedef struct {
    int state;
    int x4;
    int x8;
    int type;
    LetterType *lt;
    int x14;
    void *data;
    void *data2;
    int x20;
} Letter;

extern void *g_pLetterMem;
extern LetterType *get_letter_type(int);
extern void *iosMallocAlign(void *, int, int);
extern void func_0001BB90(Letter *, int, int, LetterType *);

/* Matches only with -fno-strict-aliasing (config/ee_cflags.json). */
Letter *create_letter(void **out_data, void **out_data2, int type, int a3, int a4)
{
    LetterType *lt = get_letter_type(type);
    Letter *l;
    if (lt != 0) {
    l = iosMallocAlign(g_pLetterMem, lt->size + lt->extra + 0x30, 0x10);
    if (l != 0) {
    l->type = type;
    l->state = 1;
    l->x4 = 0;
    l->x8 = 0;
    l->lt = lt;
    func_0001BB90(l, a3, a4, lt);
    l->data = (char *)l + 0x30;
    if (l->lt->init)
        l->lt->init(l->data);
    l->data2 = (char *)l->data + l->lt->size;
    if (l->lt->post)
        l->lt->post(l->data2);
    l->x20 = 0;
    *out_data = l->data;
    *out_data2 = l->data2;
    return l;
    }
    }
    return 0;
}
