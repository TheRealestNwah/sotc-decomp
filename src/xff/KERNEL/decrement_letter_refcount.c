extern void iosFree(void *);

int decrement_letter_refcount(int *letter)
{
    int freed = 0;

    if (*letter != 0) {
        (*(int *)*letter)--;
        if (*(int *)*letter == 0) {
            iosFree((void *)*letter);
            freed = 1;
        }
        *letter = 0;
    }
    return freed;
}
