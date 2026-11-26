typedef struct Letter {
    void *data;
    struct Letter *next;
} Letter;

typedef struct {
    int count;
    Letter *head;
    int pad8;
    Letter *cur;
    Letter *next;
} Post;

extern void *g_pLetterMem;
extern void *iosMallocAlign(void *, int, int);
extern void iosFree(void *);
extern void decrement_letter_refcount(Letter *);

void discard_all_letter_in_post(Post *p);
static void func_0001BFE8(char *pa0);

Post *create_letter_post(void)
{
    Post *p = iosMallocAlign(g_pLetterMem, 0x14, 0x10);
    func_0001BFE8((char *)p);
    return p;
}

void check_free_letter_post(Post **arg0)
{
    Post *temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0) {
        discard_all_letter_in_post(temp_v0);
        iosFree(*arg0);
        *arg0 = 0;
    }
}

void discard_all_letter_in_post(Post *p)
{
    Letter *l = p->head;
    Letter *n;
    while (l != 0) {
        n = l->next;
        decrement_letter_refcount(l);
        iosFree(l);
        l = n;
    }
    p->count = 0;
    p->head = 0;
    p->pad8 = 0;
    p->cur = 0;
    p->next = 0;
}

int get_total_letter_in_post(Post *p)
{
    return p->count;
}

void open_letter_post(Post *p)
{
    p->cur = 0;
    p->next = p->head;
}

void *get_next_letter_in_post(Post *p)
{
    Letter *l = p->next;
    void *data;
    void *r;

    if (l != 0) {
        Letter *n;
        p->cur = l;
        /* Found by the permuter; the do/while fixes the load order. */
        do {
            data = l->data;
            n = l->next;
            r = data;
        } while (0);
        p->next = n;
    } else {
        r = 0;
    }
    return r;
}

void close_letter_post(Post *p)
{
    p->cur = 0;
    p->next = 0;
}

static void func_0001BFE8(char *pa0)
{
    *(int *)(pa0 + 0x0) = 0;
    *(int *)(pa0 + 0x4) = 0;
    *(int *)(pa0 + 0x8) = 0;
    *(int *)(pa0 + 0xC) = 0;
    *(int *)(pa0 + 0x10) = 0;
}
