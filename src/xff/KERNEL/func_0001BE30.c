typedef struct {
    char pad0[0xC];
    int (*filter)(void *, void *);
} Receiver;

typedef struct {
    char pad0[0x1C];
    void *post;
} Postman;

extern void *get_letter_receiver_data(void *);
extern void push_back_letter_in_post(void *, void *);

static int func_0001BE30(Postman *p, void *letter, Receiver *r)
{
    if (r->filter) {
        if (r->filter(p, get_letter_receiver_data(letter)) != 1)
            return 0;
    }
    push_back_letter_in_post(p->post, letter);
    return 1;
}
