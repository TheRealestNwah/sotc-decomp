extern void decrement_letter_refcount(int *);
extern void push_back_letter_in_post(int, int);
extern int B_000C2750;

void send_letter(int *arg0)
{
    push_back_letter_in_post(B_000C2750, *arg0);
    decrement_letter_refcount(arg0);
    *arg0 = 0;
}
