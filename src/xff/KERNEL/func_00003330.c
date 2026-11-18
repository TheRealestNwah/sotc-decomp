/* Parked attempt: 2 words differ (order of the two argument moves before a call). */
#ifdef NONMATCHING
typedef struct Block {
    int x0;
    int x4;
    unsigned int next;
    union { unsigned int flags; struct { unsigned int lo:24; unsigned int free:1; } f; };
    char pad10[0x24 - 0x10];
    int sub;
} Block;

extern void LoaderSysPrintf(const char *, ...);
extern void func_00003028(void *, int, int, int);
extern int rootPtn;

#define NEXT(b) ((Block *)(((b)->next & 0xFFFFFF) << 2))

static void func_00003330(Block *head, Block *parent, int *count)
{
    Block *p, *start, *next;

    p = NEXT(head);
    start = p;
    while (p != 0) {
        if (p < start || (Block *)0x2000000 < p) {
            if (parent != 0) {
                func_00003028(parent, 0, 0, -1);
                LoaderSysPrintf("\033[34m\242\254\244\263\244\263\244\336\244\307\245\341\245\342\245\352\245\352\245\363\245\257\245\250\245\351\241\274\310\257\300\270\245\321\241\274\245\306\245\243\245\267\245\347\245\363\244\316\277\306\245\321\241\274\245\306\245\243\245\267\245\347\245\363\033[0m\n");
            }
            func_00003028(head, 0, 1, -1);
            LoaderSysPrintf("\033[34m\242\254\244\263\244\263\244\336\244\307\245\341\245\342\245\352\245\352\245\363\245\257\245\250\245\351\241\274\244\316\270\253\244\304\244\253\244\303\244\277\245\321\241\274\245\306\245\243\245\267\245\347\245\363\033[0m\n");
            LoaderSysPrintf("\n\033[31m\245\341\245\342\245\352\245\301\245\247\245\303\245\257\275\350\315\375\244\307\245\341\245\342\245\352\245\352\245\363\245\257\244\316\307\313\302\273\244\254\244\337\244\304\244\253\244\352\244\336\244\267\244\277\241\243\033[0m\n");
        }
        (*count)++;
        start = p;
        if ((p->flags & 0x3000000) == 0x3000000)
            func_00003330((Block *)&p->sub, head, count);
        next = NEXT(p);
        if (next != 0) {
            if (next < p || (Block *)0x2000000 < next) {
                LoaderSysPrintf("\033[34malloc %p -> next_alloc %p \245\352\245\363\245\257\244\254\262\365\244\354\244\306\244\244\244\336\244\271\033[0m\n", p, next);
                __asm__ __volatile__("break 0");
                func_00003028(&rootPtn, 0, 0, -1);
                __asm__ __volatile__("break 0");
            }
            if (next != 0 && !p->f.free && !next->f.free) {
                LoaderSysPrintf("\033[34m info %p %p \244\317\317\242\302\263\244\267\244\277\266\365\244\255\266\365\264\326\244\254\275\320\315\350\244\306\244\267\244\336\244\303\244\306\244\244\244\336\244\271\033[0m\n", p, next);
                func_00003028(head, 0, 1, -1);
            }
        }
        p = next;
    }
}
#endif
