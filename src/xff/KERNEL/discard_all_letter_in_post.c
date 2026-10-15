typedef struct Letter { int a; struct Letter *next; } Letter;
typedef struct { int a; Letter *head; int c, d, e; } Post;
extern void decrement_letter_refcount(Letter *);
extern void iosFree(void *);

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
    p->a = 0;
    p->head = 0;
    p->c = 0;
    p->d = 0;
    p->e = 0;
}
