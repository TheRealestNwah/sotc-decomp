extern void *g_pLetterMem;
extern void *iosMallocAlign(void *, int, int);
extern void increment_letter_refcount(int *);

/* The post is {count, head, tail} and each link is {letter, next, prev}.
   Both are accessed as words: the count is reloaded after the link stores,
   which only happens when every store may alias it. */
void push_back_letter_in_post(int *post, int *letter)
{
    int *link = iosMallocAlign(g_pLetterMem, 0xC, 0x10);

    link[0] = (int)letter;
    link[1] = 0;
    increment_letter_refcount(letter);
    if (post[0] == 0) {
        link[2] = 0;
        /* Head before tail keeps the two tail stores from being merged
           into a shared exit. */
        post[1] = (int)link;
        post[2] = (int)link;
    } else {
        link[2] = post[2];
        ((int *)post[2])[1] = (int)link;
        post[2] = (int)link;
    }
    post[0]++;
}
