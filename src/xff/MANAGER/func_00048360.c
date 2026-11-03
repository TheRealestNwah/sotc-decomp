extern void DeleteTwoWayLink(void *);

typedef struct {
    char pad[0xD00];
    int flag;
    char pad2[0xC];
    char link[0x80];
    char a;
    char b;
} Work;

static inline Work *GetWork(unsigned char *obj)
{
    switch (obj[8]) {
    case 9:
        return (Work *)(obj + 0x90);
    case 0x16:
        return (Work *)(obj + 0x90);
    default:
        return 0;
    }
}

static void func_00048360(unsigned char *obj)
{
    Work *w = GetWork(obj);

    if (w->flag) {
        DeleteTwoWayLink(w->link);
        w->b = 0;
        do { } while (0); /* keeps the original store order */
        w->a = 0;
        w->flag = 0;
    }
}
