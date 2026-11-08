typedef struct Letter {
    int unk0;
    struct Letter *next;
    struct Letter *prev;
} Letter;

typedef struct {
    int count;
    Letter *head;
    Letter *tail;
    Letter *sel;
    int unk10;
} Post;

extern void decrement_letter_refcount(Letter *letter);
extern void iosFree(void *p);

void discard_selecting_letter_in_post(Post *post)
{
    Letter *sel = post->sel;

    if (sel == 0) {
        return;
    }
    if (post->count == 1) {
        decrement_letter_refcount(sel);
        iosFree(sel);
        post->count = 0;
        post->head = 0;
        post->tail = 0;
        post->sel = 0;
        post->unk10 = 0;
    } else {
    if (sel == post->head) {
        post->head = sel->next;
        post->head->prev = 0;
    } else if (sel == post->tail) {
        post->tail = sel->prev;
        post->tail->next = 0;
    } else {
        sel->prev->next = sel->next;
        sel->next->prev = sel->prev;
    }
    sel = post->sel;
    decrement_letter_refcount(sel);
    iosFree(sel);
    post->sel = 0;
    post->count--;
    }
}
