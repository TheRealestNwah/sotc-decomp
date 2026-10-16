typedef struct Entry {
    int a;
    int result;
    int (*func)(struct Entry *);
} Entry;

void initSeamlessCommonLayout(char *p)
{
    int n = *(int *)(p + 0xC);
    Entry *e = *(Entry **)(p + 0x10);

    while (n--) {
        e->result = e->func(e);
        e++;
    }
}
