typedef struct Letter {
    void *data;
    struct Letter *next;
} Letter;

typedef struct {
    char pad[0xC];
    Letter *cur;
    Letter *next;
} Post;

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
