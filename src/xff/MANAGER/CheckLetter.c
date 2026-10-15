extern void open_letter_post(void *);
extern void *get_next_letter_in_post(void *);
extern void *get_letter_contents_data(void *);
extern void close_letter_post(void *);

void CheckLetter(char *o, void (*cb)(char *, void *))
{
    void *post = *(void **)(o + 0x1C);
    void *l;
    open_letter_post(post);
    while ((l = get_next_letter_in_post(post)) != 0)
        cb(o, get_letter_contents_data(l));
    close_letter_post(post);
}
