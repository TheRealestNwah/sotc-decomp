extern char *GetLayoutClass(void *);

static int func_00064300(void *layout, char *p)
{
    void *owner = *(void **)(p + 0x40);
    if (layout != owner && *(void **)(GetLayoutClass(layout) + 0x194) != owner) {
        return 1;
    }
    return 0;
}
